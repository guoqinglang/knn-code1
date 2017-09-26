
#include <float.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "params.h"
#include "distance_calc.h"
#include "nearestNeighbor.h"


typedef struct record
{
  char recString[REC_LENGTH];
  float distance;
} Record;

void findLowest(Record *records,float *distances,int *minLocations,int topN) {
  int i;
  float val;
  int minLoc1;
  Record *tempRec;
  
  for(i=0;i<topN;i++) {   // just move the k minimum records in the first k places
    minLoc1 = minLocations[i];
   
    // swap locations 
    tempRec = &records[i];
    records[i] = records[minLoc1];
    records[minLoc1] = *tempRec;
    
    // add distance to the min we found
    records[i].distance = distances[i];
  }
}

/*int load_file_to_memory(const char *filename, char **result) { 
  size_t size = 0;
  FILE *f = fopen(filename, "rb");
  if (f == NULL) 
  { 
    *result = NULL;
    return -1; // -1 means file opening fail 
  } 
  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);
  *result = (char *)malloc(size+1);
  if (size != fread(*result, sizeof(char), size, f)) 
  { 
    free(*result);
    return -2; // -2 means file reading fail 
  } 
  fclose(f);
  (*result)[size] = 0;
  return size;
}
*/

int main(int argc, char *argv[]) {
  Record *records;
  Float2 *locations;
  records =(Record *)malloc(sizeof(Record)*12);
  locations =(Float2 *)malloc(sizeof(Float2)*12);
  int i;
  
  int j=0;

  char filename[1024];
  int resultsCount=NUM_NEIGHBORS;
  int quiet=0;
  float lat=QUERY_LAT,lng=QUERY_LNG;
 
  FILE *fp;
  int numRecords=0;
  fp = fopen("/home/guo/Desktop/knn-20170915/filelist.txt", "r");
  if(!fp) {
    perror("error opening the data file\n");
    exit(1);
  }
        // read each record
  while(!feof(fp)){  //read until the end of the file

    

     Record record;
     Float2 latLong;
    fgets(record.recString,REC_LENGTH,fp);

    fgetc(fp); // newline
  //  if (feof(fp)) break;
            
    // parse for lat and long
    char str[REC_LENGTH];
    strncpy(str,record.recString,sizeof(str));
    int year, month, date, hour, num, speed, press;
    float lati, lon;
    char name[REC_LENGTH];
    sscanf(str, "%d %d %d %d %d %s %f %f %d %d ", &year, 
      &month, &date, &hour, &num, name, &lati,   &lon, &speed, &press);   

//printf("%d %d %d %d %d %s %f %f %d %d\n", year, 
 //     month, date, hour, num, name, lati,   lon, speed, press);
 
    latLong.x = lati;
    latLong.y = lon;   
//printf("latLong.y =%f\n",latLong.y);

    locations[j] = latLong;
    records[j] = record;
    printf("j =%d\n",j);
    j=j+1;

    numRecords++;
    printf("numRecords =%d\n",numRecords);
  }

  fclose(fp);
  printf("read file end \n");

  if (!quiet) {
    printf("Number of points in reference data set: %d\n",numRecords);
    printf("latitude: %f\n",lat);
    printf("longitude: %f\n",lng);
    printf("Finding the %d closest neighbors.\n",resultsCount);
  }

  if (resultsCount > numRecords)
   resultsCount = numRecords;
   printf("resultsCount: %d\n",resultsCount);

 
  float *distances = (float *)malloc(sizeof(float) * numRecords);
  float *d_distances = (float *)malloc(sizeof(float) * resultsCount);
  int *indices = (int *)malloc(sizeof(int) * resultsCount);
  
   distance_calc(locations, lat, lng, distances, numRecords);

   nearestNeighbor (distances,d_distances, indices, numRecords, resultsCount);

  // find the resultsCount least distances
  findLowest(records,d_distances,indices,resultsCount);
  free(distances);
  free(d_distances);
  free(indices);
  // print out results
   int position;
  if (!quiet)
    for(i=0;i<resultsCount;i++) {
      printf("%s --> Distance=%f\n",records[i].recString,records[i].distance);
    }

  return 0;
}

