static void
icvTeleaInpaintFMM(const CvMat *f, CvMat *t, CvMat *out, int range, CvPriorityQueueFloat *Heap ) {
   int i = 0, j = 0, ii = 0, jj = 0, k, l, q, color = 0;
   float dist;

   if (CV_MAT_CN(out->type)==3) {

      while (Heap->Pop(&ii,&jj)) {

         CV_MAT_ELEM(*f,uchar,ii,jj) = KNOWN;
         for(q=0; q<4; q++) {
            if     (q==0) {i=ii-1; j=jj;}
            else if(q==1) {i=ii;   j=jj-1;}
            else if(q==2) {i=ii+1; j=jj;}
            else if(q==3) {i=ii;   j=jj+1;}
            if ((i<=1)||(j<=1)||(i>t->rows-1)||(j>t->cols-1)) continue;

            if (CV_MAT_ELEM(*f,uchar,i,j)==INSIDE) {
               dist = min4(FastMarching_solve(i-1,j,i,j-1,f,t),
                           FastMarching_solve(i+1,j,i,j-1,f,t),
                           FastMarching_solve(i-1,j,i,j+1,f,t),
                           FastMarching_solve(i+1,j,i,j+1,f,t));
               CV_MAT_ELEM(*t,float,i,j) = dist;

               for (color=0; color<=2; color++) {
                  CvPoint2D32f gradI,gradT,r;
                  float Ia=0,Jx=0,Jy=0,s=1.0e-20f,w,dst,lev,dir,sat;

                  if (CV_MAT_ELEM(*f,uchar,i,j+1)!=INSIDE) {
                     if (CV_MAT_ELEM(*f,uchar,i,j-1)!=INSIDE) {
                        gradT.x=(float)((CV_MAT_ELEM(*t,float,i,j+1)-CV_MAT_ELEM(*t,float,i,j-1)))*0.5f;
                     } else {
                        gradT.x=(float)((CV_MAT_ELEM(*t,float,i,j+1)-CV_MAT_ELEM(*t,float,i,j)));
                     }
                  } else {
                     if (CV_MAT_ELEM(*f,uchar,i,j-1)!=INSIDE) {
                        gradT.x=(float)((CV_MAT_ELEM(*t,float,i,j)-CV_MAT_ELEM(*t,float,i,j-1)));
                     } else {
                        gradT.x=0;
                     }
                  }
                  if (CV_MAT_ELEM(*f,uchar,i+1,j)!=INSIDE) {
                     if (CV_MAT_ELEM(*f,uchar,i-1,j)!=INSIDE) {
                        gradT.y=(float)((CV_MAT_ELEM(*t,float,i+1,j)-CV_MAT_ELEM(*t,float,i-1,j)))*0.5f;
                     } else {
                        gradT.y=(float)((CV_MAT_ELEM(*t,float,i+1,j)-CV_MAT_ELEM(*t,float,i,j)));
                     }
                  } else {
                     if (CV_MAT_ELEM(*f,uchar,i-1,j)!=INSIDE) {
                        gradT.y=(float)((CV_MAT_ELEM(*t,float,i,j)-CV_MAT_ELEM(*t,float,i-1,j)));
                     } else {
                        gradT.y=0;
                     }
                  }
                  for (k=i-range; k<=i+range; k++) {
                     int km=k-1+(k==1),kp=k-1-(k==t->rows-2);
                     for (l=j-range; l<=j+range; l++) {
                        int lm=l-1+(l==1),lp=l-1-(l==t->cols-2);
                        if (k>0&&l>0&&k<t->rows-1&&l<t->cols-1) {
                           if ((CV_MAT_ELEM(*f,uchar,k,l)!=INSIDE)&&
                               ((l-j)*(l-j)+(k-i)*(k-i)<=range*range)) {
                              r.y     = (float)(i-k);
                              r.x     = (float)(j-l);

                              dst = (float)(1./(VectorLength(r)*sqrt((double)VectorLength(r))));
                              lev = (float)(1./(1+fabs(CV_MAT_ELEM(*t,float,k,l)-CV_MAT_ELEM(*t,float,i,j))));

                              dir=VectorScalMult(r,gradT);
                              if (fabs(dir)<=0.01) dir=0.000001f;
                              w = (float)fabs(dst*lev*dir);

                              if (CV_MAT_ELEM(*f,uchar,k,l+1)!=INSIDE) {
                                 if (CV_MAT_ELEM(*f,uchar,k,l-1)!=INSIDE) {
                                    gradI.x=(float)((CV_MAT_3COLOR_ELEM(*out,uchar,km,lp+1,color)-CV_MAT_3COLOR_ELEM(*out,uchar,km,lm-1,color)))*2.0f;
                                 } else {
                                    gradI.x=(float)((CV_MAT_3COLOR_ELEM(*out,uchar,km,lp+1,color)-CV_MAT_3COLOR_ELEM(*out,uchar,km,lm,color)));
                                 }
                              } else {
                                 if (CV_MAT_ELEM(*f,uchar,k,l-1)!=INSIDE) {
                                    gradI.x=(float)((CV_MAT_3COLOR_ELEM(*out,uchar,km,lp,color)-CV_MAT_3COLOR_ELEM(*out,uchar,km,lm-1,color)));
                                 } else {
                                    gradI.x=0;
                                 }
                              }
                              if (CV_MAT_ELEM(*f,uchar,k+1,l)!=INSIDE) {
                                 if (CV_MAT_ELEM(*f,uchar,k-1,l)!=INSIDE) {
                                    gradI.y=(float)((CV_MAT_3COLOR_ELEM(*out,uchar,kp+1,lm,color)-CV_MAT_3COLOR_ELEM(*out,uchar,km-1,lm,color)))*2.0f;
                                 } else {
                                    gradI.y=(float)((CV_MAT_3COLOR_ELEM(*out,uchar,kp+1,lm,color)-CV_MAT_3COLOR_ELEM(*out,uchar,km,lm,color)));
                                 }
                              } else {
                                 if (CV_MAT_ELEM(*f,uchar,k-1,l)!=INSIDE) {
                                    gradI.y=(float)((CV_MAT_3COLOR_ELEM(*out,uchar,kp,lm,color)-CV_MAT_3COLOR_ELEM(*out,uchar,km-1,lm,color)));
                                 } else {
                                    gradI.y=0;
                                 }
                              }
                              Ia += (float)w * (float)(CV_MAT_3COLOR_ELEM(*out,uchar,km,lm,color));
                              Jx -= (float)w * (float)(gradI.x*r.x);
                              Jy -= (float)w * (float)(gradI.y*r.y);
                              s  += w;
                           }
                        }
                     }
                  }
                  sat = (float)((Ia/s+(Jx+Jy)/(sqrt(Jx*Jx+Jy*Jy)+1.0e-20f)+0.5f));
                  {
                  CV_MAT_3COLOR_ELEM(*out,uchar,i-1,j-1,color) = cv::saturate_cast<uchar>(sat);
                  }
               }

               CV_MAT_ELEM(*f,uchar,i,j) = BAND;
               Heap->Push(i,j,dist);
            }
         }
      }

   } else if (CV_MAT_CN(out->type)==1) {

      while (Heap->Pop(&ii,&jj)) {

         CV_MAT_ELEM(*f,uchar,ii,jj) = KNOWN;
         for(q=0; q<4; q++) {
            if     (q==0) {i=ii-1; j=jj;}
            else if(q==1) {i=ii;   j=jj-1;}
            else if(q==2) {i=ii+1; j=jj;}
            else if(q==3) {i=ii;   j=jj+1;}
            if ((i<=1)||(j<=1)||(i>t->rows-1)||(j>t->cols-1)) continue;

            if (CV_MAT_ELEM(*f,uchar,i,j)==INSIDE) {
               dist = min4(FastMarching_solve(i-1,j,i,j-1,f,t),
                           FastMarching_solve(i+1,j,i,j-1,f,t),
                           FastMarching_solve(i-1,j,i,j+1,f,t),
                           FastMarching_solve(i+1,j,i,j+1,f,t));
               CV_MAT_ELEM(*t,float,i,j) = dist;

               for (color=0; color<=0; color++) {
                  CvPoint2D32f gradI,gradT,r;
                  float Ia=0,Jx=0,Jy=0,s=1.0e-20f,w,dst,lev,dir,sat;

                  if (CV_MAT_ELEM(*f,uchar,i,j+1)!=INSIDE) {
                     if (CV_MAT_ELEM(*f,uchar,i,j-1)!=INSIDE) {
                        gradT.x=(float)((CV_MAT_ELEM(*t,float,i,j+1)-CV_MAT_ELEM(*t,float,i,j-1)))*0.5f;
                     } else {
                        gradT.x=(float)((CV_MAT_ELEM(*t,float,i,j+1)-CV_MAT_ELEM(*t,float,i,j)));
                     }
                  } else {
                     if (CV_MAT_ELEM(*f,uchar,i,j-1)!=INSIDE) {
                        gradT.x=(float)((CV_MAT_ELEM(*t,float,i,j)-CV_MAT_ELEM(*t,float,i,j-1)));
                     } else {
                        gradT.x=0;
                     }
                  }
                  if (CV_MAT_ELEM(*f,uchar,i+1,j)!=INSIDE) {
                     if (CV_MAT_ELEM(*f,uchar,i-1,j)!=INSIDE) {
                        gradT.y=(float)((CV_MAT_ELEM(*t,float,i+1,j)-CV_MAT_ELEM(*t,float,i-1,j)))*0.5f;
                     } else {
                        gradT.y=(float)((CV_MAT_ELEM(*t,float,i+1,j)-CV_MAT_ELEM(*t,float,i,j)));
                     }
                  } else {
                     if (CV_MAT_ELEM(*f,uchar,i-1,j)!=INSIDE) {
                        gradT.y=(float)((CV_MAT_ELEM(*t,float,i,j)-CV_MAT_ELEM(*t,float,i-1,j)));
                     } else {
                        gradT.y=0;
                     }
                  }
                  for (k=i-range; k<=i+range; k++) {
                     int km=k-1+(k==1),kp=k-1-(k==t->rows-2);
                     for (l=j-range; l<=j+range; l++) {
                        int lm=l-1+(l==1),lp=l-1-(l==t->cols-2);
                        if (k>0&&l>0&&k<t->rows-1&&l<t->cols-1) {
                           if ((CV_MAT_ELEM(*f,uchar,k,l)!=INSIDE)&&
                               ((l-j)*(l-j)+(k-i)*(k-i)<=range*range)) {
                              r.y     = (float)(i-k);
                              r.x     = (float)(j-l);

                              dst = (float)(1./(VectorLength(r)*sqrt(VectorLength(r))));
                              lev = (float)(1./(1+fabs(CV_MAT_ELEM(*t,float,k,l)-CV_MAT_ELEM(*t,float,i,j))));

                              dir=VectorScalMult(r,gradT);
                              if (fabs(dir)<=0.01) dir=0.000001f;
                              w = (float)fabs(dst*lev*dir);

                              if (CV_MAT_ELEM(*f,uchar,k,l+1)!=INSIDE) {
                                 if (CV_MAT_ELEM(*f,uchar,k,l-1)!=INSIDE) {
                                    gradI.x=(float)((CV_MAT_ELEM(*out,data_type,km,lp+1)-CV_MAT_ELEM(*out,data_type,km,lm-1)))*2.0f;
                                 } else {
                                    gradI.x=(float)((CV_MAT_ELEM(*out,data_type,km,lp+1)-CV_MAT_ELEM(*out,data_type,km,lm)));
                                 }
                              } else {
                                 if (CV_MAT_ELEM(*f,uchar,k,l-1)!=INSIDE) {
                                    gradI.x=(float)((CV_MAT_ELEM(*out,data_type,km,lp)-CV_MAT_ELEM(*out,data_type,km,lm-1)));
                                 } else {
                                    gradI.x=0;
                                 }
                              }
                              if (CV_MAT_ELEM(*f,uchar,k+1,l)!=INSIDE) {
                                 if (CV_MAT_ELEM(*f,uchar,k-1,l)!=INSIDE) {
                                    gradI.y=(float)((CV_MAT_ELEM(*out,data_type,kp+1,lm)-CV_MAT_ELEM(*out,data_type,km-1,lm)))*2.0f;
                                 } else {
                                    gradI.y=(float)((CV_MAT_ELEM(*out,data_type,kp+1,lm)-CV_MAT_ELEM(*out,data_type,km,lm)));
                                 }
                              } else {
                                 if (CV_MAT_ELEM(*f,uchar,k-1,l)!=INSIDE) {
                                    gradI.y=(float)((CV_MAT_ELEM(*out,data_type,kp,lm)-CV_MAT_ELEM(*out,data_type,km-1,lm)));
                                 } else {
                                    gradI.y=0;
                                 }
                              }
                              Ia += (float)w * (float)(CV_MAT_ELEM(*out,data_type,km,lm));
                              Jx -= (float)w * (float)(gradI.x*r.x);
                              Jy -= (float)w * (float)(gradI.y*r.y);
                              s  += w;
                           }
                        }
                     }
                  }
                  sat = (float)((Ia/s+(Jx+Jy)/(sqrt(Jx*Jx+Jy*Jy)+1.0e-20f)+0.5f));
                  {
                  CV_MAT_ELEM(*out,data_type,i-1,j-1) = cv::saturate_cast<data_type>(sat);
                  }
               }

               CV_MAT_ELEM(*f,uchar,i,j) = BAND;
               Heap->Push(i,j,dist);
            }
         }
      }
   }
}