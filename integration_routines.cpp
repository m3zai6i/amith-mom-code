/*
 *  integration_routines.cpp
 *  MOM EFIE
 *
 *  Created by Conor Brennan on 20/07/2011.
 *  Copyright 2011 Dublin City University. All rights reserved.
 *
 */

#include	"integration_routines.h"
#include	"complex.hh"
#include	"point3d.hh"
#include	"global_definitions.h"
#include	"ComplexVector.hh"
#include    "complex_functions.hpp"

double ro (double phi, double q, double m)
{
	return (q/(sin(phi)-m*cos(phi)));
}


complex fa (double k, double xcp, double q, double m, double phi)
{
	complex ta, qa, pa;
	double mul;
	double r = ro(phi,q,m);
	
	ta = cos(phi)+complex(0.0,k*xcp);
	pa = polar (1.0, -k*r);
	qa = complex (0.0, k*r*cos(phi)) + cos(phi) + complex (0.0, k*xcp);
	mul = - 1.0 / pow (k, 2.0);
	return (mul * (ta - pa * qa));
}

complex fb (double k, double ycp, double q, double m, double phi)
{
	complex tb, qb, pb;
	double mul;
	double r = ro(phi,q,m);
	
	tb = sin(phi)+complex(0.0,k*ycp);
	pb = polar (1.0, -k*r);
	qb = complex (0.0, k*r*sin(phi)) + sin(phi) + complex (0.0, k*ycp);
	mul = - 1.0 / pow (k, 2.0);
	return (mul * (tb - pb * qb));
}

complex fc (double k, double q, double m, double phi)
{
	double r = ro(phi,q,m);
	complex unity = complex(1.0 , 0.0 ) ; 
	
	
	complex mul = unity  / complex (0.0, k);
	complex p = polar (1.0, -k*r);
	return ((1.0 - p)*mul);
	
}


complex fun1 (double k, double eta, double csi, CPoint3d r1, 
              CPoint3d r2, CPoint3d r3, CPoint3d rcp,  int the_self_term)
{
	complex num, den;
	CPoint3d r;
	double e, Rp;
	complex temp ; 
	
	
	r = r1 *csi  + r2 * eta  + r3* (1 - csi - eta) ;
	Rp = sqrt ( (rcp - r) * (rcp - r) );
	
		temp =1.0/Rp ;  
	
	e = - k * Rp;
	num = polar (1.0, e)*temp ; 
	den = 1.0 ;
	return (num / den);
}

complex fun2 (double k, double eta, double csi, CPoint3d r1, 
              CPoint3d  r2, CPoint3d r3, CPoint3d rcp, int the_self_term)
{
	complex num, den; 
	CPoint3d r;
	double e , Rp;
    complex temp ; 
	
	
	
	r = r1*csi  +  r2 *eta  + r3* (1 - csi - eta) ;
	Rp = sqrt ( (rcp - r ) * ( rcp - r) );
	
	    temp =1.0/Rp ;
	
	e = - k * Rp;
	num = csi * polar (1.0, e)*temp;
	den = 1.0 ;
	return (num / den);
}

complex fun3 (double k, double eta, double csi, CPoint3d  r1,  
              CPoint3d r2, CPoint3d r3, CPoint3d rcp,int the_self_term)
{
	complex num, den;
	CPoint3d r;
	double e, Rp;
	complex temp ; 
	
	
	r =  r1*csi  + r2* eta  + r3* (1 - csi - eta) ; 
	Rp = sqrt ( (rcp - r) * (  rcp -r) );
	    temp =1.0/Rp ;
	
	
	e = - k * Rp;
	num = eta * polar (1.0, e)*temp ;
	den = 1.0 ; 
	return (num / den);
}


complex rcs_fun1 (double k, double eta, double csi, CPoint3d r1, 
              CPoint3d r2, CPoint3d r3, CPoint3d rcp)
{
	complex num, den;
	CPoint3d r;
	double e;
	double temp ; 
	
	
	r = r1 *csi  + r2 * eta  + r3* (1 - csi - eta) ;
	temp =  (rcp*r)/rcp.abs() ;
	
	
	e =  k * temp;
	num = polar (1.0, e) ; 
	
	return num ;
}

complex rcs_fun2 (double k, double eta, double csi, CPoint3d r1, 
              CPoint3d  r2, CPoint3d r3, CPoint3d rcp)
{
	complex num, den; 
	CPoint3d r;
	double e ;
    double temp ; 
	
	r = r1 *csi  + r2 * eta  + r3* (1 - csi - eta) ;
	temp =  (rcp*r)/rcp.abs() ;
	
	
	e =  k * temp;
	num = csi*polar (1.0, e) ; 
	
	return num ;
	
}

complex rcs_fun3 (double k, double eta, double csi, CPoint3d  r1,  
              CPoint3d r2, CPoint3d r3, CPoint3d rcp)
{
	complex num, den;
	CPoint3d r;
	double e;
	double temp ; 
	
	r = r1 *csi  + r2 * eta  + r3* (1 - csi - eta) ;
	temp =  (rcp*r)/rcp.abs() ;
	
	e =  k * temp;
	num = eta*polar (1.0, e) ; 
	
	return num ;
	}



// The function imped is taken from Luca's code. 
// It is used in calculating non self term matrix elements. 
void imped (CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d centr, complex *I, complex *Icsi, complex *Ieta, double the_wave_number,  int the_self_term )
{
	double k = the_wave_number;
	int j;
	int P = 7;
	complex res1, res2, res3;
	double csi=0.0554630355;
	double csi1=0.2956689642;
	double eta=0.0554632748;
	double eta1=0.6337734837;
	double ww=0.0209871755;
	double w1=0.1123286156;
	double wu=0.1000526268;
	double fc[]={csi1,eta,eta1,csi,0.3333333,1-eta-csi,1-eta1-csi1};
	double fe[]={eta1,1-eta-csi,1-eta1-csi1,eta,0.3333333,csi,csi1};
	double al[]={w1,ww,w1,ww,wu,ww,w1};
	
	
	
	res1 = res2 = res3 = complex (0.0, 0.0);
	
	
	for (j=0; j<P; j++)
	{
		res1 += al[j]*fun1(k,fe[j],fc[j],r1,r2,r3,centr,the_self_term);
		res2 += al[j]*fun2(k,fe[j],fc[j],r1,r2,r3,centr,the_self_term);
    res3 += al[j]*fun3(k,fe[j],fc[j],r1,r2,r3,centr,the_self_term);  }
	
	*I = res1;
	*Icsi = res2;
	*Ieta = res3;
	
	return;
	
}




complex factor (CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d ro1, CPoint3d ro2, CPoint3d ro3,
				double ln, double mult, double obs_triangle, int opt, double the_wave_number,  int self_term)
{
	CPoint3d origin, x_p, y_p;
	double the_omega ; 
	double dot_prod_real, dot_prod_imag ;
	complex sum_l, sum_m;
	CPoint3d c1;
	complex a, b, c;
	CPoint3d prodr, prodi, A_real, A_imag ;
	CPoint3d proj;
	complex I, I2, Icsi, Icsi2, Ieta, Ieta2, phi ;
	complex a0, K1, K2 ;
double area ; 
	
	CPoint3d rocm;
	
	
	// evaluate the centroid of the triangle
	
	c1 = (ro1 + ro2 + ro3) / 3.0;
	
	// calculate rocm
	
	rocm = (c1 - ro1)*obs_triangle ;
	
	// calculate prodr and prodi
	
	
	imped (r1, r2, r3, c1, &I, &Icsi, &Ieta, the_wave_number, self_term );
	
	
    
	prodr = r1 * Icsi.real() + r2 * Ieta.real() +
	r3 * (I - Icsi - Ieta).real() - r1 * I.real() ;
	prodi = r1 * Icsi.imag() + r2 * Ieta.imag()  +
	r3 * (I - Icsi - Ieta).imag() - r1 * I.imag();
	
	
	// approximate the integral
	
	c1 = cross (ro2 - ro1, ro3 - ro1);
	area = sqrt ( (c1 * c1)) / 2.0;
	
	
	the_omega = the_wave_number/sqrt( mu * eps );
    A_real  = prodr*(mult*(mu*ln) / (4.0*pi))  ; 
	A_imag  = prodi*(mult*(mu*ln) / (4.0*pi)) ; 
	
		phi = complex(0.0,1.0)*(mult*ln*I/(2.0*pi*the_omega*eps)) ; 
	
	dot_prod_real = 0.5*(A_real * rocm)  ; 
    dot_prod_imag = 0.5*(A_imag * rocm)  ; 
	sum_l = (complex(0.0,the_omega) * complex(dot_prod_real,dot_prod_imag) ) - obs_triangle*phi ; 
	
	
	return sum_l; 
	
	
	
	
}

complex patch (CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d ro1, CPoint3d ro2, CPoint3d ro3,
               double ln, double mult, double obs_triangle , double Aq, int opt, double the_wave_number)
{
	CPoint3d origin, x_p, y_p;
	double the_omega , mod  ;
	complex sum_l, sum_m;
	CPoint3d c1;
	complex a, b, c;
	CPoint3d proj;
	complex Magnx, Magny, Phi;
	
	complex a0;
	
	CPoint3d origin1, x_p1, y_p1;
	CPoint3d Mre, Mim;
	complex dot_prod, phi, K1 , K2  ; 
	CPoint3d rocm;
	double xcp, ycp, area ;
	
	// define the coordinate system of the observation domain
	
	//cout << " r1 equals " << r1 << endl ; 
	//cout << " r2 equals " << r2 << endl ; 
	//cout << " r3 equals " << r3 << endl ; 
	//cout << " ro1 equals " << ro1 << endl ; 
	//cout << " ro2 equals " << ro2 << endl ; 
	//cout << " ro3 equals " << ro3 << endl ; 
	
	origin = ro1;
	x_p = ro3 - origin;
	mod = sqrt ((x_p*x_p));
	x_p = x_p * ( 1.0 / mod );
	proj = x_p *  ((ro2 - origin)* x_p);
	y_p = ro2 - origin - proj;
	mod = sqrt ((y_p* y_p));
	y_p = y_p * ( 1.0 / mod );
	
	// and of the basis domain
	
	origin1 = r1;
	x_p1 = r3 - origin1;
	mod = sqrt ((x_p1* x_p1));
	x_p1 = x_p1 * ( 1.0 / mod );
	proj = x_p1 * ((r2 - origin1)* x_p1);
	y_p1 = r2 - origin1 - proj;
	mod = sqrt ((y_p1* y_p1));
	y_p1 = y_p1 * ( 1.0 / mod );
	
	
	// evaluate the centroid of the triangle
	
	c1 = (ro1 + ro2 + ro3) / 3.0;
	
	// now the components of rocm
	
	rocm = (c1 - ro1)*obs_triangle;
	xcp =  (rocm* x_p);
	ycp =  (rocm* y_p);
	
	// evaluate M
	
	
	the_omega = the_wave_number/sqrt(eps*mu) ; 
	
	self (r1, r2, r3, &Magnx, &Magny, &Phi, Aq, c1, the_wave_number);
	
	Mre = CPoint3d(x_p1 * Magnx.real() + y_p1 * Magny.real());
	Mim = CPoint3d(x_p1 * Magnx.imag() + y_p1 * Magny.imag());
	Magnx = complex ( (Mre*x_p),  (Mim* x_p));
	Magny = complex ( (Mre* y_p), (Mim* y_p));
	
	c1 = cross (ro2 - ro1, ro3 - ro1);
	area = sqrt ( (c1*c1)) / 2.0;
	
	
	dot_prod =  (mult * ln * mu  * Magnx * xcp) /( 16.0*pi*Aq) 
	+  (mult * ln * mu* Magny * ycp)  / ( 16.0*pi*Aq)   ; 
	
		
    phi = obs_triangle*mult*complex(0.0,1.0)*ln*Phi/(4.0*pi*the_omega*eps*Aq) ; 
	
	sum_l = complex(0.0, the_omega)*dot_prod  -  phi;
	
	
	
	
	return (sum_l);
	
}



void self (CPoint3d r1, CPoint3d r2, CPoint3d r3,  complex *Magnx, 
           complex *Magny, complex *Phi, double Aq, CPoint3d centr, double the_wave_number) 
{
	double k  ; 
	int j;
	double xr, xm, dx;
	double ab[]={0.09501250983763744018531933542,
		0.2816035507792589132304605014,
		0.4580167776572273863424194429,
		0.6178762444026437484466717640,
		0.7554044083550030338951011948,
		0.8656312023878317438804678977,
		0.9445750230732325760779884155,
	0.9894009349916499325961541734};  
	double w[]={0.1894506104550684962853967232,
		0.1826034150449235888667636679,
		0.1691565193950025381893120790,
		0.1495959888165767320815017305,
		0.1246289712555338730534762821,
		0.09515851168249278480992510760,
		0.06225352393864789286284383699,
	0.02715245941175409485178057245};
	int N = 8;
	
	
	double b;
	double a;
	
	CPoint3d origin, x_p, y_p, proj;
	complex Ix, Iy;
	complex Ix1, Iy1;
	complex Ix2, Iy2;
	complex Ix3, Iy3;
	complex P;
	complex P1;
	complex P2;
	complex P3;
	double phia, phib, slope, shift;
	double x_pa, y_pa, x_pb, y_pb, x_cp, y_cp;
	double mod;
	
	double infty = 1e18;
	double epsilon = 1e-16;
	
	
	k = the_wave_number ; 
	
	// calculate numerically the integral
	// define the unit vectors x_p and y_p
	
	origin = r1;
	x_p = r3 - origin;
	mod = sqrt ( (x_p*x_p));
	x_p = x_p * ( 1.0 / mod );
	proj = x_p *  ((r2 - origin)* x_p);
	y_p = r2 - origin - proj;
	mod = sqrt ( (y_p*y_p));
	y_p = y_p * ( 1.0 / mod );
	
	// evaluate the coordinates with respect to x_p and y_p
	
	x_cp =  ((centr - origin)* x_p);
	y_cp =  ((centr - origin)* y_p);
	
	// operate on Tq1
	
	// find the coefficients of the line passing by the two points
	
	x_pa = ((r2-centr)*x_p);
	y_pa = ((r2-centr)*y_p);
	x_pb = ((r1-centr)*x_p);
	y_pb = ((r1-centr)*y_p);
	
	if ((x_pa-x_pb)==0) slope = infty; else
		slope = (y_pa - y_pb) / (x_pa - x_pb);
	shift = y_pa - slope * x_pa;
	
	if ((slope<epsilon)&&(shift==0))
	{
		Ix1 = Iy1 = P1 = complex (0.0, 0.0);
	}
	
	else{
		
		// evaluate phia and phib
		
		phia = atan2 (y_pa,x_pa);
		
		phib = atan2 (y_pb,x_pb);
		
		// try now with Gaussian rule
		
		a = phia;
		b = phib;
		if (b<a) b += 2*3.141592654;
		
		xm = 0.5 * (b+a);
		xr = 0.5 * (b-a);
		
		Ix1 = Iy1 = P1 = complex (0.0, 0.0);
		
		for (j=0; j<N; j++)
		{
			dx = xr * ab[j];
			Ix1 += w[j] * (fa(k,x_cp,shift,slope,xm+dx)+fa(k,x_cp,shift,slope,xm-dx));
			Iy1 += w[j] * (fb(k,y_cp,shift,slope,xm+dx)+fb(k,y_cp,shift,slope,xm-dx));
			P1 += w[j] * (fc(k,shift,slope,xm+dx)+fc(k,shift,slope,xm-dx));
		}
		
		Ix1 *= xr;
		Iy1 *= xr;
	P1 *= xr;}
	
	// operate on Tq2
	
	// find the coefficients of the line passing by the two points
	
	x_pa = ( (r3-centr)* x_p);
	y_pa = ( (r3-centr)* y_p);
	x_pb = ( (r2-centr)* x_p);
	y_pb = ( (r2-centr)* y_p);
	
	if ((x_pa-x_pb)==0) slope = infty; else
		slope = (y_pa - y_pb) / (x_pa - x_pb);
	shift = y_pa - slope * x_pa;
	
	if ((slope<epsilon)&&(shift==0))
	{
		Ix2 = Iy2 = P2 = complex (0.0, 0.0);
	}
	
	else{
		
		// evaluate phia and phib
		
		phia = atan2 (y_pa,x_pa);
		
		phib = atan2 (y_pb,x_pb);
		
		// try now with Gaussian rule
		
		a = phia;
		b = phib;
		if (b<a) b += 2*3.141592654;
		
		xm = 0.5 * (b+a);
		xr = 0.5 * (b-a);
		
		Ix2 = Iy2 = P2 = complex (0.0, 0.0);
		
		for (j=0; j<N; j++)
		{
			dx = xr * ab[j];
			Ix2 += w[j] * (fa(k,x_cp,shift,slope,xm+dx)+fa(k,x_cp,shift,slope,xm-dx));
			Iy2 += w[j] * (fb(k,y_cp,shift,slope,xm+dx)+fb(k,y_cp,shift,slope,xm-dx));
			P2 += w[j] * (fc(k,shift,slope,xm+dx)+fc(k,shift,slope,xm-dx));
		}
		
		Ix2 *= xr;
		Iy2 *= xr;
	P2 *= xr;}
	
	// operate on Tq3
	
	// find the coefficients of the line passing by the two points
	
	x_pa = ( (r1-centr)* x_p);
	y_pa = ( (r1-centr)* y_p);
	x_pb = ( (r3-centr)* x_p);
	y_pb = ( (r3-centr)* y_p);
	
	if ((x_pa-x_pb)==0) slope = infty; else
		slope = (y_pa - y_pb) / (x_pa - x_pb);
	shift = y_pa - slope * x_pa;
	
	if ((slope<epsilon)&&(shift==0))
	{
		Ix3 = Iy3 = P3 = complex (0.0, 0.0);
	}
	
	else{
		
		// evaluate phia and phib
		
		phia = atan2 (y_pa,x_pa);
		
		phib = atan2 (y_pb,x_pb);
		
		// try now with Gaussian rule
		
		a = phia;
		b = phib;
		if (b<a) b += 2*3.141592654;
		
		xm = 0.5 * (b+a);
		xr = 0.5 * (b-a);
		
		Ix3 = Iy3 = P3 = complex (0.0, 0.0);
		
		for (j=0; j<N; j++)
		{
			dx = xr * ab[j];
			Ix3 += w[j] * (fa(k,x_cp,shift,slope,xm+dx)+fa(k,x_cp,shift,slope,xm-dx));
			Iy3 += w[j] * (fb(k,y_cp,shift,slope,xm+dx)+fb(k,y_cp,shift,slope,xm-dx));
			P3 += w[j] * (fc(k,shift,slope,xm+dx)+fc(k,shift,slope,xm-dx));
		}
		
		Ix3 *= xr;
		Iy3 *= xr;
	P3 *= xr;}
	
	Ix = Ix1 + Ix2 + Ix3;
	Iy = Iy1 + Iy2 + Iy3;
	P = P1 + P2 + P3;
	
	// *Magnx = (1.0/(2.0*Aq))*Ix;
	// *Magny = (1.0/(2.0*Aq))*Iy;
	// *Phi = (1.0/(2.0*Aq))*P; 
	// I like to return the unscaled values... 
	// Luca used to divide by the 2.0*area ? 
	
	*Magnx = Ix;
	*Magny = Iy;
	*Phi = P; 
	
	
	return ;
}





/* Code used in computing scattered fields at a point */ 

CComplexVector  A_scatter( CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d field_point, double lj, double the_wave_number) 
{
	
	CComplexVector E   = CComplexVector(0.0 , 0.0 , 0.0 )  ; 
	complex I , Icsi, Ieta ; 
	CPoint3d prodr , prodi ; 
	double the_omega ; 
	the_omega = the_wave_number/sqrt( mu * eps );
	// calculate prodr and prodi
	
	imped (r1, r2, r3, field_point, &I, &Icsi, &Ieta, the_wave_number,0);
	
    
	prodr = r1 * Icsi.real() + r2 * Ieta.real() +
	r3 * (I - Icsi - Ieta).real() - r1 * I.real() ;
	prodi = r1 * Icsi.imag() + r2 * Ieta.imag()  +
	r3 * (I - Icsi - Ieta).imag() - r1 * I.imag();
	
	prodr = prodr*the_omega*mu*lj/(4.0*pi)  ; 
	prodi = prodi*the_omega*mu*lj/(4.0*pi)  ; 
	E = CComplexVector(prodr, prodi ) ; 
	E = E*complex(0.0, -1.0 )  ; 
	
	return E ; 
	
}



CComplexVector  phi_scatter( CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d field_point, double lj, double the_wave_number) 
{
	
	CComplexVector E   = CComplexVector(0.0 , 0.0 , 0.0 )  ; 
	complex I , Icsi, Ieta ; 
	CPoint3d prodr , prodi ; 
	double the_omega ; 
	the_omega = the_wave_number/sqrt( mu * eps );
	// calculate prodr and prodi
	
	imped2 (r1, r2, r3, field_point, &I, &Icsi, &Ieta, the_wave_number);
	
    
	prodr = r1 * Icsi.real() + r2 * Ieta.real() +
	r3 * (I - Icsi - Ieta).real() - field_point * I.real() ;
	prodi = r1 * Icsi.imag() + r2 * Ieta.imag()  +
	r3 * (I - Icsi - Ieta).imag() - field_point * I.imag();
	
	prodr = prodr*lj/(2.0*pi*eps*the_omega)  ; 
	prodi = prodi*lj/(2.0*pi*eps*the_omega)  ; 
	E = CComplexVector(prodr, prodi ) ; 
	E = E*complex(0.0,1.0 )  ; 
	
	
	return E ; 
	
}
/********************************************************************/



void imped2 (CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d centr, complex *I2, complex *Icsi, complex *Ieta, double the_wave_number)
{
	double k = the_wave_number;
	int j;
	int P = 7;
	complex res1, res2, res3;
	double csi=0.0554630355;
	double csi1=0.2956689642;
	double eta=0.0554632748;
	double eta1=0.6337734837;
	double ww=0.0209871755;
	double w1=0.1123286156;
	double wu=0.1000526268;
	double fc[]={csi1,eta,eta1,csi,0.3333333,1-eta-csi,1-eta1-csi1};
	double fe[]={eta1,1-eta-csi,1-eta1-csi1,eta,0.3333333,csi,csi1};
	double al[]={w1,ww,w1,ww,wu,ww,w1};
	
	
	
	res1 = res2 = res3 = complex (0.0, 0.0);
	
	
	for (j=0; j<P; j++)
	{
		res1 += al[j]*phi_fun1(k,fe[j],fc[j],r1,r2,r3,centr);
		res2 += al[j]*phi_fun2(k,fe[j],fc[j],r1,r2,r3,centr);
		res3 += al[j]*phi_fun3(k,fe[j],fc[j],r1,r2,r3,centr);
		
	}
	
	*I2 = res1;
	*Icsi = res2;
	*Ieta = res3;
	
	return;
	
}


complex phi_fun1 (double k, double eta, double csi, CPoint3d r1, 
				  CPoint3d r2, CPoint3d r3, CPoint3d rcp)
{
	complex num, den;
	CPoint3d r;
	double e, Rp;
	complex temp ; 
	
	
	
	r = r1 *csi  + r2 * eta  + r3* (1 - csi - eta) ;
	Rp = sqrt ( (rcp - r) * (rcp - r) );
	
	temp = complex(1.0,k*Rp) ; 
	
	e = - k * Rp;
	num = polar (1.0, e)*temp ; 
	den = Rp*Rp*Rp ;
	return (num / den);
}

complex phi_fun2 (double k, double eta, double csi, CPoint3d r1, 
				  CPoint3d  r2, CPoint3d r3, CPoint3d rcp)
{
	complex num, den; 
	CPoint3d r;
	double e , Rp;
    complex temp ; 
	
	
	
	r = r1*csi  +  r2 *eta  + r3* (1 - csi - eta) ;
	Rp = sqrt ( (rcp - r ) * ( rcp - r) );

	
	temp = complex(1.0,k*Rp) ; 
	e = - k * Rp;
	
	
	num = csi * polar (1.0, e)*temp;
	den = Rp*Rp*Rp ;
	return (num / den);
}

complex phi_fun3 (double k, double eta, double csi, CPoint3d  r1,  
				  CPoint3d r2, CPoint3d r3, CPoint3d rcp)
{
	complex num, den;
	CPoint3d r;
	double e, Rp;
	complex temp ; 
	
	
	r =  r1*csi  + r2* eta  + r3* (1 - csi - eta) ; 
	Rp = sqrt ( (rcp - r) * (  rcp -r) );
	
	temp = complex(1.0,k*Rp) ; 
	
	e = - k * Rp;
	num = eta* polar (1.0, e)*temp ; 
	den = Rp*Rp*Rp ;
	
	return (num / den);
}



CComplexVector  RCS_scatter( CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d field_point, double lj, double the_wave_number) 
{
	
	complex I , Icsi, Ieta ; 
	CPoint3d prodr , prodi ; 
	CComplexVector A , phi ; 
	double temp ; 
	
	imped_rcs (r1, r2, r3, field_point, &I, &Icsi, &Ieta, the_wave_number);
	prodr = r1 * Icsi.real() + r2 * Ieta.real() +
	r3 * (I - Icsi - Ieta).real() - r1 * I.real() ;
	prodi = r1 * Icsi.imag() + r2 * Ieta.imag()  +
	r3 * (I - Icsi - Ieta).imag() - r1 * I.imag();
	
	A = CComplexVector(complex(prodr.xcoord(),prodi.xcoord()),complex(prodr.ycoord(),prodi.ycoord()),complex(prodr.zcoord(),prodi.zcoord())) ; 
	
	A = A*complex(0.0,-omega*mu*lj/(4.0*pi)) ; 
	temp = -the_wave_number*lj/(2.0*omega*pi*eps) ; 
	phi = CComplexVector(field_point.xcoord()*I*temp,field_point.ycoord()*I*temp,field_point.zcoord()*I*temp) ; 
	
	
	return (A + phi)  ; 
	
}


void imped_rcs (CPoint3d r1, CPoint3d r2, CPoint3d r3, CPoint3d centr, complex *I, complex *Icsi, complex *Ieta, double the_wave_number )
{
	double k = the_wave_number;
	int j;
	int P = 7;
	complex res1, res2, res3;
	double csi=0.0554630355;
	double csi1=0.2956689642;
	double eta=0.0554632748;
	double eta1=0.6337734837;
	double ww=0.0209871755;
	double w1=0.1123286156;
	double wu=0.1000526268;
	double fc[]={csi1,eta,eta1,csi,0.3333333,1-eta-csi,1-eta1-csi1};
	double fe[]={eta1,1-eta-csi,1-eta1-csi1,eta,0.3333333,csi,csi1};
	double al[]={w1,ww,w1,ww,wu,ww,w1};
	
	
	
	res1 = res2 = res3 = complex (0.0, 0.0);
	
	
	for (j=0; j<P; j++)
	{
		res1 += al[j]*rcs_fun1(k,fe[j],fc[j],r1,r2,r3,centr);
		res2 += al[j]*rcs_fun2(k,fe[j],fc[j],r1,r2,r3,centr);
    res3 += al[j]*rcs_fun3(k,fe[j],fc[j],r1,r2,r3,centr);  }
	
	*I = res1;
	*Icsi = res2;
	*Ieta = res3;
	
	return;
	
}


