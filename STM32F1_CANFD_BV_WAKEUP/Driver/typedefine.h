/********************************************************************
filename : typedefine.h
discript : define some type whitch not declared in lib.
********************************************************************/

#ifndef __TYPEDEFINE_H__
#define __TYPEDEFINE_H__

#define TRUE			1
#define FALSE			0

#define SUCCESS		1
#define FAIL			0


#define ON				1
#define OFF				0


#define	HIGH			1
#define LOW				0


typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;


#endif

