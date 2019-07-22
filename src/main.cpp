//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//
//  Name:       main.cpp
//  Synopsis:   This is the startup routine
//
//  WARNING: This will not compile with the default gcc binaries.
//  Use at least gcc 7
//

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "aphd.hpp"

using namespace std;

int main()
{
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;
   
#ifdef _DEBUG
    cout << "Compiled with _DEBUG" << endl;
#endif

   for( i = 0; i < NUM_THREADS; i++ ) {
#ifdef _DEBUG
      cout << "main() : creating thread, " << i << endl;
#endif

      rc = pthread_create(&threads[i], NULL, runThread, (void *)i);
      
      if (rc) {
         cerr << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

