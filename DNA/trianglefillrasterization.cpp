  #include "trianglefillrasterization.h"

   void triangle::Createtriangle()//draw  a triangle from 3 points which must be different
   {


     line(renderer,p1,p2,rgb).Drawline();
     line(renderer,p2,p3,rgb).Drawline();
     line(renderer,p1,p3,rgb).Drawline();

     if ((p1==p2)||(p2==p3)||(p1==p3))
     std::cout<<"triangle can't be created";
   }


   void triangle::Filltriangle()//fills the triangle using horizontal line from top to bottom
   {
      point temp1, temp2;
       bool flag=true;
          color updatecolore1,updatecolore2,updatecolore3;
      if(p1.y==p2.y)//used in case of right angled triangle
      {
          temp1=p1;
          temp2=p2;
          line e1(renderer,temp1,p3,rgb);
          line e2(renderer,temp2,p3,rgb);
         line(renderer,temp1,temp2,rgb).Drawline();
         while(flag)
         {
            if(e1.Returnupdatedcoordinate())
          {
              if(e2.Returnupdatedcoordinate())
              {
                if(e1.slopelessthan1)
                updatecolore1=e1.xcolorupdate;
                else
                updatecolore1=e1.ycolorupdate;
                if(e2.slopelessthan1)
                updatecolore2=e2.xcolorupdate;
                else
                updatecolore2=e2.ycolorupdate;
                  temp1=point(e1.xupdate,e1.yupdate,updatecolore1);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2);
                  line(renderer,temp1,temp2,rgb).Drawline();

              }
          }
          if(temp1.y == p3.y)
          flag=false;
         }
      }
     else if(p2.y==p3.y)//used in case of right angled triangle
      {
          temp1=p2;
          temp2=p3;
          line e1(renderer,temp1,p1,rgb);
          line e2(renderer,temp2,p1,rgb);
          line(renderer,temp1,temp2,rgb).Drawline();
          while(flag)
         {
            if(e1.Returnupdatedcoordinate())
          {
              if(e2.Returnupdatedcoordinate())
              {
                  if(e1.slopelessthan1)
                updatecolore1=e1.xcolorupdate;
                else
                updatecolore1=e1.ycolorupdate;
                if(e2.slopelessthan1)
                updatecolore2=e2.xcolorupdate;
                else
                updatecolore2=e2.ycolorupdate;
                  temp1=point(e1.xupdate,e1.yupdate,updatecolore1);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2);
                  line(renderer,temp1,temp2,rgb).Drawline();

              }
          }
          if(temp1.y == p1.y)
          flag=false;
         }
      }
      else//used for other triangles except right angled triangle
     {
         temp1=p3;
         temp2=p3;
      line e1(renderer,temp1,p2,rgb);
      line e2(renderer,temp2,p1,rgb);
      line e3(renderer,p2,p1,rgb);
      while(flag)//loop runs until the level of p2(intermediate point ) is reached
      {

          if(e1.Returnupdatedcoordinate())//enter only after increment in y
          {
              if(e2.Returnupdatedcoordinate())
              {
                  if(e1.slopelessthan1)
                updatecolore1=e1.xcolorupdate;
                else
                updatecolore1=e1.ycolorupdate;
                if(e2.slopelessthan1)
                updatecolore2=e2.xcolorupdate;
                else
                updatecolore2=e2.ycolorupdate;
                  temp1=point(e1.xupdate,e1.yupdate,updatecolore1);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2);
                  line(renderer,temp1,temp2,rgb).Drawline();//for drawing horizontal line between two updated point

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
                updatecolore1=e3.xcolorupdate;
                else
                updatecolore1=e3.ycolorupdate;
                if(e2.slopelessthan1)
                updatecolore2=e2.xcolorupdate;
                else
                updatecolore2=e2.ycolorupdate;
                  temp1=point(e3.xupdate,e3.yupdate,updatecolore3);
                  temp2=point(e2.xupdate,e2.yupdate,updatecolore2);
                  line(renderer,temp1,temp2,rgb).Drawline();
              }
          }
          if(temp1.y==p1.y)
              flag=false;
      }

   }
   }
