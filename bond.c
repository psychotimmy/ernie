#include <stdio.h> 
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
 
#define TOTALBONDS 6000000
#define WINODDS    2.45
#define BONDSHELD  5
#define TOTALDRAWS 984
 
 
double rand0to1()
{
    	/* return a pseudorandom number between 0 and 1 */
 
        return ((double)rand()/(double)RAND_MAX);
}
 
void main()
{
        int prizes, winner, i, drawnumber, prizesallocated; 
        int blocktotal=0, singletotal=0, oldtotal=0, newtotal=0;
 
        /* Different bondholder types and their bond numbers */
        int blockbonds[BONDSHELD]={200000,200001,200002,200003,200004};
       	int singlebonds[BONDSHELD]={10534,248491,1000302,4000522,5200976};
        int oldbonds[BONDSHELD]={1,10,100,1000,10000};
        int newbonds[BONDSHELD]={5999900,5999910,5999920,5999930,5999940};
 
	bool allbonds[TOTALBONDS]; 
 
        /* Seed the pseudorandom number generator */
        srand(time(NULL));
 
        /* Total prizes are calculated using current NS&I odds of 24,500 to 1 per bond held, scaled to 2.45 to 1 per bond held for this simulation */
        /* The total number of bonds in ciruclation is also scaled back by the same propotion, from around 60 billion to 6 million */
        /* Therefore the maximum holding in this simulation is 5 bonds, equivalent to 50,000 in the real draw */
        /* Average luck implies each bondholder should win 2.04 times per draw - the same as in the real draw*/
 
        /* Run the draw multiple times - 12 is equivalent to 1 year's worth of real draws */
 
        for (drawnumber=0; drawnumber<TOTALDRAWS; drawnumber++) {
 
       		/* Set up the draw - no-one has won yet */
        	for (i=0;i<TOTALBONDS;i++)  { 
			        allbonds[i]=false; 
        	}
 
        	/* Work out the total number of prizes */
		      prizes = (int) (TOTALBONDS / WINODDS);
 
        	/* Draw a new bond to win until all prizes are allocated */
        	prizesallocated=0;
        	while (prizesallocated<prizes) {
            		winner = (int) (rand0to1()*TOTALBONDS);
            		/* The NS&I rules state that the same bond cannot win twice in the same draw */
           		  /* prizesallocated is not incremented in this event and the prize is reallocated */
            		if (!allbonds[winner]) {
               			allbonds[winner] = true;
               	 		++prizesallocated;
            		}
        	}
 
        	/* Check each bondholder against the draw, and increment the total number of times they have won */
          printf("\nWinners for draw %d\n",drawnumber+1);
		      for (i=0;i<BONDSHELD;i++) {
  			      if (allbonds[blockbonds[i]]) { printf("Block bond %d wins!\n",blockbonds[i]); ++blocktotal; }
  			      if (allbonds[singlebonds[i]]) { printf("Single bond %d wins!\n",singlebonds[i]); ++singletotal; }
  			      if (allbonds[oldbonds[i]])  { printf("Old bond %d wins!\n",oldbonds[i]); ++oldtotal; }
  			      if (allbonds[newbonds[i]]) { printf("New bond %d wins!\n",newbonds[i]); ++newtotal; }
        	}
	      }
 
        /* Calculate what the average luck was for each of the bondholders */
 
	      printf("\nSummary of results\n");
        printf("Block bond holder won on average %.2f times per draw\n", (float) blocktotal/TOTALDRAWS);
        printf("Single bond holder won on average %.2f times per draw\n", (float) singletotal/TOTALDRAWS);
        printf("Old bond holder won on average %.2f times per draw\n", (float) oldtotal/TOTALDRAWS);
        printf("New bond holder won on average %.2f times per draw\n", (float) newtotal/TOTALDRAWS);
 
}
