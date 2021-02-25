/*
 * 1) Get arguments (files to be sent to Gist)
 * 2) Initialize cURL
 * 3) JSON-encode data
 */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

struct curl_slist *prepare_headers(char *content_length, char *authorization)
{
	struct curl_slist *chunk = NULL;

	chunk = curl_slist_append(chunk, "Host: gist.github.com");
	chunk = curl_slist_append(chunk, "Accept: application/vnd.github.v3+json");
	chunk = curl_slist_append(chunk, "Content-Type: application/json");
	chunk = curl_slist_append(chunk, content_length);
	chunk = curl_slist_append(chunk, authorization);
	chunk = curl_slist_append(chunk, "User-Agent: c-curl-gist-creator");
	return chunk;
}

char *read_file(FILE *fd)
{
	char *file_content;
	int file_len;
	int file_read;

	fseek(fd, 0, SEEK_END);
	file_len = ftell(fd);
	file_content = malloc(file_len + 1);

	fseek(fd, 0, SEEK_SET);
	file_read = fread(file_content, 1, file_len, fd);
	printf("file len: %d, read: %d, ptr: %p\n", file_len, file_read, file_content);
	file_content[file_len] = '\0';
	printf("file content %s %p\n", file_content, file_content);
	return file_content;
}

char *read_files(char **files, int num_files)
{
	FILE *fd;
	char *file_content;
	int file_len;
	json_t *obj, *str;

	obj = json_object();

	for (int i = 0; i < num_files; i++)
	{
		char *filename = files[i];
		fd = fopen(filename, "r");
		file_content = read_file(fd);
		str = json_string(file_content);
		file_content[file_len] = '\0';
		json_object_set(obj, filename, str);
		json_decref(str);
		fclose(fd);
		free(file_content);
	}
	return json_dumps(obj, 0);
}

int main(int argc, char **argv)
{
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;
	char *payload;
	char **files = argv + 1;
	int num_files = argc - 1;
	char *content_length;
	char content_length_val[8];
	char *authorization;
	char *token;
	FILE *fdtok;

	curl = curl_easy_init();
	if (!curl)
	{
		printf("Could not init cURL, aborting!\n");
		return 1;
	}

	printf("#1\n");

	payload = read_files(files, num_files);
	// should check that file exists and is 40-char long
	fdtok = fopen("token", "r");
	token = read_file(fdtok);
	fclose(fdtok);

	printf("#2\n");

	// "Authorization: token " (21 bytes) + 40-byte token + null char
	authorization = malloc(62);
	strcpy(authorization, "Authorization: token ");
	strcat(authorization, token);

	// "Content-Length: " (16 bytes) + payload len + null char
	sprintf(content_length_val, "%ld", strlen(payload));
	content_length = malloc(17 + strlen(content_length_val));
	strcpy(content_length, "Content-Length: ");
	strcat(content_length, content_length_val);

	printf("Token          >>\t%s\n", token);
	printf("Authorization  >>\t%s\n", authorization);
	printf("Content-Length >>\t%s\n", content_length);
	printf("Payload        >>\t%s\n", payload);

	headers = prepare_headers(content_length, authorization);

	// curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/gists");
	// curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
	// curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	// res = curl_easy_perform(curl);
	// if (res != CURLE_OK)
	// 	fprintf(stderr, "curl_easy_perform() failed: %s\n",
	// 			curl_easy_strerror(res));

	// curl_easy_cleanup(curl);
	// curl_global_cleanup();

	free(token);
	free(authorization);
	free(content_length);
	free(payload);
}
