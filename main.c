#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

// Declare mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Declare thread func
void *thread_func(void *arg);

// Struct for fragments
typedef struct {

	char *data;
	int length;

} FRAGMENT_T;

FRAGMENT_T **fragments = NULL;

int num_files = 0;

int main(int argc, char **argv) {

	// Declare threads array
	pthread_t *tids = NULL;

	struct dirent *entry;
		
	// Create file pointer for mp3 file
	char *writepath = strdup(argv[2]);
	FILE *write_fp = fopen(writepath, "wb");

	// switch current working directory to dir given on command line
	chdir(argv[1]);
	
	// open the current working directory
	DIR *current = opendir(".");
	
	// Initialize iterator for # of threads
	int i = 0;

	// read entries and output based on type
	while( (entry = readdir(current)) ) {
		if (entry->d_type == DT_DIR && strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,"..") != 0) {
		
			printf("Viewing top level directory: %s\n", entry->d_name);
			
			// Reallocate threads array
			tids = realloc(tids, sizeof(pthread_t)*(i+1));
			
			// Create new path
			int len = strlen(entry->d_name) + 1;
			char *subpath = malloc(len);
			snprintf(subpath, len, "%s", entry->d_name);
			
			// Make new thread & pass to thread function
			pthread_create(&tids[i], NULL, thread_func, subpath);
			
			// Iterate
			i = i + 1;
			
		}
	}
	
	// Join threads
	for (int j = 0; j < i; j++) {
	    pthread_join(tids[j], NULL);
	}
	
	
	// Write to file
	
	// Write data to file
	for (int i=0; i<num_files; i++) {
		
		fwrite(fragments[i]->data, 1, fragments[i]->length, write_fp);
	
	}
	
	
	// Free up
	free(tids);
	for (int i=0; i<num_files; i++) {
		free(fragments[i]->data);
	}
	free(fragments);
	fclose(write_fp);


return 0;
}


void *thread_func(void *arg) {

	char *path = (char *)arg;
	
	struct dirent *entry;
	
	// open the current working directory
	DIR *current = opendir(path);

	// read entries and output based on type
	while( (entry = readdir(current)) ) {
		if (entry->d_type == DT_DIR && strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,"..")) {
			
			// Print to console
			printf("Opening: %s\n", entry->d_name);
			
			// Create new path
			int len = strlen(path) + 1 + strlen(entry->d_name) + 1;
			char *subpath = malloc(len);
			snprintf(subpath, len, "%s/%s", path, entry->d_name);
			
			// Recursively call thread_func
			thread_func(subpath);
			
		} else if (entry->d_type == DT_REG) {
		
			// Print to console
			printf("Found file: %s\n", entry->d_name);
		
			// Get current file number
			char *tempstr = malloc(3);
			strncpy(tempstr, entry->d_name, 3);
			tempstr[2] = 0;
			int cur_num = atoi(tempstr);
			
			
			// Open file
			
			// Create new path to file
			int len = strlen(path) + 1 + strlen(entry->d_name) + 1;
			char *binpath = malloc(len);
			snprintf(binpath, len, "%s/%s", path, entry->d_name);
			
			FILE *fp = fopen(binpath, "r");
			
			// Read file to temp char*
			
			// Get size of file
			fseek(fp, 0, SEEK_END);
			int n = ftell(fp);
			rewind(fp);
			
			// Declare and allocate tempdata var
			char *tempdata = malloc(n);
			
			// Read file to temp data
			fread(tempdata, 1, n, fp);
		
			
			// CRITICAL SECTION
			pthread_mutex_lock(&mutex);
			
			// Resize fragments array if needed
			if (num_files <= cur_num) {
				num_files = cur_num + 1;
				fragments = realloc(fragments, num_files*sizeof(FRAGMENT_T*));
			}
			
			// Copy to array
			
			// Allocate memory for fragments element
			fragments[cur_num] = malloc(sizeof(FRAGMENT_T));
			
			// Resize fragments member & copy
			fragments[cur_num]->data = malloc(n);
			memcpy(fragments[cur_num]->data, tempdata, n);
			
			// Copy data from n to length
			fragments[cur_num]->length = n;
			
			pthread_mutex_unlock(&mutex);
			// END CRITICAL SECTION
			
			// Close file
			fclose(fp);
		
		}	
	}
	return 0;
}



