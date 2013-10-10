/* 
 * File:   stdhf.h
 * Author: Cory
 *
 * Created on October 8, 2013, 2:37 PM
 */

#ifndef STDHF_H
#define	STDHF_H

#define WHITE 'O'
#define BLACK '@'
#define EMPTY '_'
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

//Struct to define a coordinate pair in the board, one data piece for both row and column
//Operators +, +=, - and -= defined to add or subtract the row and col members from two coordPairs
typedef struct coordPair{
    int row;
    int col;
    coordPair& operator+=(const coordPair& rhs){
         this->row+=rhs.row;
         this->col+=rhs.col;
         return *this;
    }
    coordPair& operator-=(const coordPair& rhs){
         this->row-=rhs.row;
         this->col-=rhs.col;
         return *this;
    }
} coordPair;

inline coordPair operator+(coordPair lhs, const coordPair& rhs)
{
  lhs += rhs;
  return lhs;
}
inline coordPair operator-(coordPair lhs, const coordPair& rhs)
{
  lhs -= rhs;
  return lhs;
}
#endif	/* STDHF_H */

