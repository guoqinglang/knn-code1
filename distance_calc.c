//#include "params.h"
#include "distance_calc.h"
#include<stdio.h>


void distance_calc( Float2 d_locations[50],
                     const float lat,
		     const float lng,
		     float dist[2000],
	       	      int numRecords) {


	int count = *(int*)&numRecords;
	
        for(int globalId = 0; globalId < count; globalId++){

		float lat_tmp, lng_tmp, dist_lat, dist_lng;

		// using temporaries for the latitude and longitude
		lat_tmp = d_locations[globalId].x;
		lng_tmp = d_locations[globalId].y;

		printf("lat_tmp=%f,lng_tmp=%f\n",lat_tmp,lng_tmp);


		dist_lat = lat-lat_tmp;
		dist_lng = lng-lng_tmp;

		//squared euclidean distance calculation
		dist[globalId] = (dist_lat*dist_lat) + (dist_lng*dist_lng);
		printf("dist[%d]=%f\n",globalId,dist[globalId]);
	}
}
