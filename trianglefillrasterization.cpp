  #include "trianglefillrasterization.h"



   void triangle::Createtriangle()//draw  a triangle from 3 points which must be different
   {
          if ((p1==p2)||(p2==p3)||(p1==p3))
{
  return;
}

     line(p1,p2).Drawline();
     line(p2,p3).Drawline();
     line(p1,p3).Drawline();
   }

   void triangle::Filltriangle()//fills the triangle using horizontal line from top to bottom
   {
          if ((p1==p2)||(p2==p3)||(p1==p3))
{
  return;
}
bool shadowflag=false;
if(p1.shadow or p2.shadow or p3.shadow)
shadowflag=true;

//      Createtriangle();
      point temp1, temp2;

          color updatecolore1,updatecolore2,updatecolore3;
         float updatezbuffere1,updatezbuffere2,updatezbuffere3;
      {
      if(p1.y==p2.y)//used in case of right angled triangle
      {
          temp1=p1;
          temp2=p2;
          line e1(temp1,p3);
          line e2(temp2,p3);
         line(temp1,temp2).Drawhorizontalline();
         for(int i=0;i<fabs(p1.y-p3.y);i++)
         {
            if(e1.Returnupdatedcoordinate())
          {
              if(e2.Returnupdatedcoordinate())
              {
                if(e1.slopelessthan1)
                {
                   updatecolore1=e1.xcolorupdate;
                   updatezbuffere1=e1.xzbufferupdate;
                }
                else
                {
                 updatecolore1=e1.ycolorupdate;
                 updatezbuffere1=e1.yzbufferupdate;
                }
                if(e2.slopelessthan1)
                {
                 updatecolore2=e2.xcolorupdate;
                 updatezbuffere2=e2.xzbufferupdate;
                }
                else
                {
                 updatecolore2=e2.ycolorupdate;
                 updatezbuffere2=e2.yzbufferupdate;
                }
                  temp1=point(e1.xupdate,e1.yupdate,updatecolore1,updatezbuffere1,shadowflag);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2,updatezbuffere2,shadowflag);
                  line(temp1,temp2).Drawhorizontalline();
              }
          }
         }

      }
     else if(p2.y==p3.y)//used in case of right angled triangle
      {
          temp1=p2;
          temp2=p3;
          line e1(temp1,p1);
          line e2(temp2,p1);
          line(temp1,temp2).Drawhorizontalline();
           for(int i=0;i<fabs(p1.y-p2.y);i++)
         {
            if(e1.Returnupdatedcoordinate())
          {
              if(e2.Returnupdatedcoordinate())
              {
                  if(e1.slopelessthan1)
               {
                 updatecolore1=e1.xcolorupdate;
                 updatezbuffere1=e1.xzbufferupdate;
               }
                else
                {
                 updatecolore1=e1.ycolorupdate;
                 updatezbuffere1=e1.yzbufferupdate;
                }
                if(e2.slopelessthan1)
                {
                updatecolore2=e2.xcolorupdate;
                updatezbuffere2=e2.xzbufferupdate;
                }
                else
                {
                 updatecolore2=e2.ycolorupdate;
                 updatezbuffere2=e2.yzbufferupdate;
                }

                  temp1=point(e1.xupdate,e1.yupdate,updatecolore1,updatezbuffere1,shadowflag);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2,updatezbuffere2,shadowflag);
                  line(temp1,temp2).Drawhorizontalline();
              }
          }

         }
      }
      else//used for other triangles except right angled triangle
     {
       bool flag=true;
         temp1=p3;
         temp2=p3;
      line e1(temp1,p2);
      line e2(temp2,p1);
      line e3(p2,p1);
      while(flag)//loop runs until the level of p2(intermediate point ) is reached
      {

          if(e1.Returnupdatedcoordinate())//enter only after increment in y
          {
              if(e2.Returnupdatedcoordinate())
              {
                  if(e1.slopelessthan1)
                  {
                    updatecolore1=e1.xcolorupdate;
                    updatezbuffere1=e1.xzbufferupdate;
                  }
                else
                {
                 updatecolore1=e1.ycolorupdate;
                 updatezbuffere1=e1.yzbufferupdate;
                }
                if(e2.slopelessthan1)
                {
                  updatecolore2=e2.xcolorupdate;
                  updatezbuffere2=e2.xzbufferupdate;
                }
                else
                {
                 updatecolore2=e2.ycolorupdate;
                 updatezbuffere2=e2.yzbufferupdate;
                }

                  temp1=point(e1.xupdate,e1.yupdate,updatecolore1,updatezbuffere1,shadowflag);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2,updatezbuffere2,shadowflag);
                  line(temp1,temp2).Drawhorizontalline();//for drawing horizontal line between two updated point
              }
          }
          if(temp2.y == p2.y)
          {
          flag=false;
          }
      }
      flag=true;
       while(flag)
      {
          if(e3.Returnupdatedcoordinate())
          {
              if(e2.Returnupdatedcoordinate())
              {
                  if(e3.slopelessthan1)
                  {
                   updatecolore3=e3.xcolorupdate;
                   updatezbuffere3=e3.xzbufferupdate;
                  }
                else
                {
                  updatecolore3=e3.ycolorupdate;
                  updatezbuffere3=e3.yzbufferupdate;
                }
                if(e2.slopelessthan1)
                {
                 updatecolore2=e2.xcolorupdate;
                 updatezbuffere2=e2.xzbufferupdate;
                }
                else
                {
                 updatecolore2=e2.ycolorupdate;
                 updatezbuffere2=e2.yzbufferupdate;
                }
                  temp1=point(e3.xupdate,e3.yupdate,updatecolore3,updatezbuffere3,shadowflag);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2,updatezbuffere2,shadowflag);
                  line(temp1,temp2).Drawhorizontalline();
              }
          }
          if(temp1.y==p1.y)
              flag=false;
      }

   }
   }
   }
