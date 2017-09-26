//#include "params.h"
#include "nearestNeighbor.h"
#include<stdio.h>
#include<stdlib.h>

// This computes the resultsCount nearest neighbors, one per work item.
void nearestNeighbor (
                float dist[1000],
                float d_distances[100],
		int indices[100],
		int N,
		int k
		)
 {


	float dist1; 
	//int N = *(int*)&numRecords;

	//int k = *(int*)&resultsCount;   // count=2  number of the k nearest points
	printf("count=%d\n",k);

        int max,position, localId, i,j;
for(localId = 0;localId < k;localId++){  //put the first k value of arrary dist into d_distances[]
   d_distances[localId]=dist[localId];
   indices[localId]=localId;
}

for(i = k;i < N;i++){   // N is the number of points,N=10
   max=0;
   dist1 = dist[i];

  for(j =0; j< k;j++) {   //k is number of the top-k minimum value,k=5
     if(d_distances[j]>max){
         max = d_distances[j]; 
	 position=j;    //j the positon of the maximum value in the array d_distances[]
     }

  }    
       if(dist1 < max){
        d_distances[position] = dist1;
        indices[position] = i;
       }

}
 for(localId=0;localId < k; localId++) 
	      printf("d_distances[%d]=%f , at position=%d\n",localId,d_distances[localId], indices[localId]);

	
}
	/*	float temp;
		int k, counter,localId,position;
		float dist1;

	 for (k  = 0; k < numR; k++) {     //k=i
		dist1 = dist[k];
		counter = k;
		if(k ==0){
		
			for( localId=0;localId < count; localId++) {
				 d_distances[localId]=dist1;
				indices[localId]=0;
			     printf("k=0,d_distances[%d]=%f,indices[%d]=%d\n",localId, d_distances[localId],localId, indices[localId]);
			}
			
		}
		else{   //in this case,k>0

			for( localId=0;localId < count; localId++) {  // j = localId
				if(dist1<d_distances[localId]){
				    position = indices[localId];
				    temp = d_distances[localId];
				    d_distances[localId]=dist1;
				    indices[localId] = counter;
				    dist1=temp;
				    counter=position;
				    	  
				    }
				
				if(dist1==d_distances[localId])
				    break;
			}
	
		}			

	}*/
	
