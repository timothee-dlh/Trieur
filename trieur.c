#include "stdio.h"
#include "dirent.h"
#include "errno.h"
#include "string.h"

int main(int argc, char* argv[]){

      struct iterLoop {
      int MAX_CHAR, MAX_FILES;
      int iterFiles, iterChar;
      }iter;
     
      struct iterLoop *pIter = &iter;

      iter.MAX_CHAR = 300; iter.MAX_FILES = 1000;

      struct dirent *pDirent;

      char* filename;
      char extension [10];
      DIR *pDir;      
      
      if (argc != 2){
            printf("Please specify the directory name in argument");
            return 1;
      }

      pDir = opendir (argv[1]);
      if (pDir == NULL){
            printf("Cannot open the directory\n");
            return 1;
      }
      
      while ((pDirent = readdir(pDir)) != NULL && iter.iterFiles < iter.MAX_FILES ){
            filename = pDirent->d_name;
            
            while (*filename != '\0' && iter.iterChar < iter.MAX_CHAR){
                  if(strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0){
                        (void)printf("%c", *filename);
                       
                        if(*filename == '.'){
                       
                              (void)printf("point detected\n");
                              filename ++; 
                       
                              for (int i; *filename != '\0' || *filename == ' '; i ++){
                                   extension[i] = *filename;
                                   (void)printf("%c", extension[i]);
                                   filename ++;
                               }              
                        } 
                  }else{
                       goto nextFile;
                  } 
                  // Extension stockée dans extension
                  iter.iterChar ++; filename ++;
                  for(int i; i <= strlen(extension); i++){
                      strcpy(extension, "");
                  }
            }
                  
            (void)printf("\n"); 
nextFile:     
             pIter->iterFiles ++, pIter->iterChar = 0; 
      }
      if(closedir(pDir) != 0){
            printf("Can't close the directory");
            return 1;
      }
      return 0;
}
