/*****************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * $Id: ftpupload.c,v 1.7 2005/01/20 14:24:56 bagder Exp $
 */

#include <stdio.h>

#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE !(FALSE)
#endif

/*
 * This example shows an FTP upload, with a rename of the file just after
 * a successful upload.
 *
 * Example based on source code provided by Erick Nuwendam. Thanks!
 */

#define LOCAL_FILE      "/tmp/uploadthis.txt"
#define UPLOAD_FILE_AS  "while-uploading.txt"
#define REMOTE_URL      "ftp://olenska.newio.org/"  UPLOAD_FILE_AS
#define RENAME_FILE_TO  "renamed-and-fine.txt"

int main(int argc, char **argv)
{
  CURL *curl;
  CURLcode res;
  FILE *ftpfile;
  FILE * hd_src ;
  int hd ;
  struct stat file_info;
  int i;

  struct curl_slist *headerlist=NULL;
  char buf_1 [] = "RNFR " UPLOAD_FILE_AS;
  char buf_2 [] = "RNTO " RENAME_FILE_TO;

  /* get the file size of the local file */
  hd = open(LOCAL_FILE, O_RDONLY) ;

  if (hd == -1) {
	fprintf(stderr, "File not found.\n");
	return(-1);
  }

  fstat(hd, &file_info);
  close(hd) ;

  printf("File size is %d\n", (int) file_info.st_size);

  /* get a FILE * of the same file, could also be made with
     fdopen() from the previous descriptor, but hey this is just
     an example! */
  hd_src = fopen(LOCAL_FILE, "rb");

  if (hd_src == NULL) {
	fprintf(stderr, "File not found.\n");
	return(-1);
  }

  /* In windows, this will init the winsock stuff */
  if (0 != curl_global_init(CURL_GLOBAL_ALL)) {
	fprintf(stderr, "error: curl global_init() failed.\n");
	return(-1);
  }

  /* get a curl handle */
  curl = curl_easy_init();

  if (curl == NULL) {
	fprintf(stderr, "error: curl_easy_init() failed.\n");
	return(-1);
  } else {

    int ret;

    /* build a list of commands to pass to libcurl */
    headerlist = curl_slist_append(headerlist, buf_1);

    if (headerlist == NULL) {
	fprintf(stderr, "error: curl_slist_append() failed.\n");
	return(-1);
    }

    headerlist = curl_slist_append(headerlist, buf_2);

    if (headerlist == NULL) {
	fprintf(stderr, "error: curl_slist_append() failed.\n");
	return(-1);
    }

    /* enable uploading */
    ret = curl_easy_setopt(curl, CURLOPT_UPLOAD, TRUE) ;

    if (0 != ret) {
      fprintf(stderr, "error: curl_easy_setopy() failed.\n");
      return(-1);
    }

    /* specify target */
    ret = curl_easy_setopt(curl, CURLOPT_URL, REMOTE_URL);

    if (0 != ret) {
      fprintf(stderr, "error: curl_easy_setopy() failed.\n");
      return(-1);
    }

    /* pass in that last of FTP commands to run after the transfer */
    ret = curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);

    if (0 != ret) {
      fprintf(stderr, "error: curl_easy_setopy() failed.\n");
      return(-1);
    }

    /* now specify which file to upload */
    ret = curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);

    if (0 != ret) {
      fprintf(stderr, "error: curl_easy_setopy() failed.\n");
      return(-1);
    }

    ret = curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE);

    if (0 != ret) {
      fprintf(stderr, "error: curl_easy_setopy() failed.\n");
      return(-1);
    }

    ret = curl_easy_setopt(curl, CURLOPT_USERPWD, "cnystrom:CHANGEME");

    if (0 != ret) {
      fprintf(stderr, "error: curl_easy_setopy() failed.\n");
      return(-1);
    }

    /* NOTE: if you want this example to work on Windows with libcurl as a
       DLL, you MUST also provide a read callback with
       CURLOPT_READFUNCTION. Failing to do so will give you a crash since a
       DLL may not use the variable's memory when passed in to it from an app
       like this. */

    /* Set the size of the file to upload (optional).  If you give a *_LARGE
       option you MUST make sure that the type of the passed-in argument is a
       curl_off_t. If you use CURLOPT_INFILESIZE (without _LARGE) you must
       make sure that to pass in a type 'long' argument. */
//   ret = curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
//                    (curl_off_t) file_info.st_size);
    ret = curl_easy_setopt(curl, CURLOPT_INFILESIZE,
                     (long) file_info.st_size);

    if (0 != ret) {
      fprintf(stderr, "error: curl_easy_setopy() failed.\n");
      return(-1);
    }

    /* Now run off and do what you've been told! */
    res = curl_easy_perform(curl);

    if (0 != res) {
      fprintf(stderr, "error: curl_easy_perform() failed.\n");
      return(-1);
    }

    /* clean up the FTP commands list */
    curl_slist_free_all (headerlist);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  if (hd_src != NULL) {
  	fclose(hd_src); /* close the local file */
  }

  curl_global_cleanup();

  return 0;
}
