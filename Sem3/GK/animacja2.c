/* 
   Pilka, ktora po wprawieniu w ruch odbija sie od scian. W trakcie odbicia pilka ugina sie
   o wielkosc zalezna od predkosci oraz troche zwalnia przy odbiciu              
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include <math.h>

#define TRUE 1
#define FALSE 0


int main(int argc, char *argv[])
{
  char            icon_name[] = "Icon";
  char            title[]     = "Nacisnik lewy klawisz i przeciagnij kursor by nadac predkosc";
  Display *       display;
  Window          window;    
  GC              gc;            
  XEvent          event;     
  KeySym          key;       
  XSizeHints      info;  
  int             screen_no;    
  unsigned long   foreground; 
  unsigned long   background;  
  char            buffer[8];   
  int             hm_keys;      

  int             to_end;       
  XPoint          lines[1000];   
  int             hm_lines = 0;     
  XPoint          current_point, previous_point; 
  int             i;
  //kolorki
  Colormap	  colormap;   		
  
  display    = XOpenDisplay("");
  screen_no  = DefaultScreen(display);
  
  background = WhitePixel(display, screen_no);
  foreground = BlackPixel(display, screen_no);
  
  colormap = DefaultColormap(display,screen_no);


  // kolory w trybie 24-bitowym:
  unsigned int blue = 255;
  unsigned int orange = 256*256*255 + 256*140 + 20;   // 256*256*Red + 256*Green + Blue
  
  info.x = 200;       
  info.y = 250;
  info.width = 640;   
  info.height = 480;  
  info.flags = PPosition | PSize;
  

  window = XCreateSimpleWindow(display, DefaultRootWindow(display),
			       info.x, info.y, info.width, info.height, 
			       20/* grubosc ramki */, foreground, background);
  XSetStandardProperties(display, window, title, icon_name, None, 
			 argv, argc, &info);
  gc = XCreateGC(display, window, 0, 0);


  XSetBackground(display, gc, background);
  XSetForeground(display, gc, foreground);

  int input_mask = KeyPressMask | ExposureMask | ButtonPressMask| PointerMotionMask| 
    //ResizeRedirectMask |
    ButtonReleaseMask | Button1MotionMask | FocusChangeMask | EnterWindowMask |LeaveWindowMask;

  XSelectInput(display, window, (input_mask));
  XMapRaised(display, window);
  
  int button_pressed = 0;   // czy klawisz myszy jest nacisniety 
  
  int R = 30;                                                // promien pilki   
  int Rx = R, Ry = R;                                        // promienie elipsy po splaszczeniu pilki uderzajacej o sciane
  int x_obj = info.width/2, y_obj = info.height/2;           // polozenie poczatkowe pilki  
  int Vx = 0, Vy = 0;                                        // predkosc pilki
 
  
  struct timeb t, t_poprz;  
  
  long liczbapetli = 0;
  to_end = FALSE;
  while (to_end == FALSE)
  {

    while (XPending(display) == 0)  // dopoki liczba komunikatow w kolejce == 0 
    {
        
      ftime(&t);                                        // czas aktualny
      if ((t.millitm % 40 == 0)&&(t.millitm != t_poprz.millitm))        // co 40 ms odswiezaj - odpowiednik Timera
      {
        XWindowAttributes xwAttr;                   
        XGetWindowAttributes(display,window,&xwAttr);   // odczyt atrybutow okna           
        info.width = xwAttr.width;                      // modyfkacja parametrow okna
	info.height = xwAttr.height;
	info.x = xwAttr.x;       
        info.y = xwAttr.y;
        
      
        // parametry animacji - ruchu obiektu: 
        x_obj += Vx;                                    // zmiana polozenia pod wplywem predkosci
        y_obj += Vy;
        int przekroczenie_x = 0, przekroczenie_y = 0;
        if ((x_obj + R >= info.width)||(x_obj - R <= 0))  // odbicie od bandy lewej lub prawej
        {
          przekroczenie_x = (x_obj + R >= info.width ? x_obj + R - info.width : R - x_obj); 
          
          x_obj -= Vx/2;
          if (przekroczenie_x > abs(Vx))
            Vx = -Vx;                      
        }
        
        if ((y_obj + R >= info.height)||(y_obj - R <= 0)) // odbicie od bandy gornej lub dolnej
        {
          przekroczenie_y = (y_obj + R >= info.height ? y_obj + R - info.height : R - y_obj);

          y_obj -= Vy/2;
          if (przekroczenie_y > abs(Vy))
            Vy = -Vy;
           
        }
        Rx = R-przekroczenie_x+przekroczenie_y;
        Ry = R-przekroczenie_y+przekroczenie_x;


        t_poprz = t;
        
        event.type = Expose;	  
	event.xexpose.count = 0;
	XSendEvent(display, window, 0, ExposureMask, &event);  // wymuszenie komunikatu z zadaniem odswiezenia okna
      }
    }  
    //XCheckWindowEvent(display, window,input_mask,&event);
    XNextEvent(display, &event);         // pobranie z bufora kolejnego komunikatu       
    switch(event.type)
    {
      case Expose:                       // zadanie odrysowania okna
	if (event.xexpose.count == 0) 
	{	  
	  XClearWindow(display, window);                  // czyszczenie okna
          
          XSetForeground(display, gc, orange);            // ustawienie koloru obiektu
          //XSetForeground(display, gc, foreground);
          XFillArc(display, window, gc, x_obj-Rx,y_obj-Ry,Rx*2,Ry*2,0,360*64);	
          XSetForeground(display, gc, foreground);  
          XDrawArc(display, window, gc, x_obj-Rx,y_obj-Ry,Rx*2,Ry*2,0,360*64);	    		      
	}
	break;
      case ResizeRequest:                      // zmiana rozmiarow okna 
      {
        char lan[64];
        sprintf(lan,"Zmiana rozmiarow okna na (%d,%d)\n",event.xresizerequest.width,event.xresizerequest.height);
        XDrawImageString(display, window, gc, 20, 20, lan, strlen(lan));
        event.type = Expose;	  
        event.xexpose.count = 0;
        XSendEvent(display, window, 0, ExposureMask, &event);
        
        printf("Rozmiary okna = (%d,%d)\n",event.xresizerequest.width,event.xresizerequest.height);
	break;
      }
      case FocusIn:                            // okno stalo sie aktywne               
        XSetForeground(display, gc, blue);
	XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 20, 20, "FocusIn", strlen("FocusIn"));
	break;
      case FocusOut:                           // okno przestalo byc aktywne
        XSetForeground(display, gc, blue);
	XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 20, 20, "FocusOut", strlen("FocusOut"));
	break;
      case EnterNotify:                        // kursor myszki znalazl sie w obszarze okna
        XSetForeground(display, gc, blue);
	XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 20, 40, "EnterNotify", strlen("EnterNotify"));
	break;
      case LeaveNotify:                        // kursor myszki znalazl sie poza obszarem okna
        XSetForeground(display, gc, blue);
	XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 20, 40, "LeaveNotify", strlen("FocusOut"));
	break;
      //case MappingNotify:
      //	XRefreshKeyboardMapping(&event.xmapping);
	
	break;
      case MotionNotify:                        // ruch myszy
      {
              if (button_pressed)
              {

                current_point.x = event.xbutton.x;
                current_point.y = event.xbutton.y;
                char lan[64];
                sprintf(lan,"ruszono myszka w punkt (%d,%d)",current_point.x,current_point.y);
                printf("%s\n",lan);
                XSetForeground(display, gc, blue); 
                XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 
		           20, 20, lan, strlen(lan));
                event.type = Expose;	  
                event.xexpose.count = 0;
                XSendEvent(display, window, 0, ExposureMask, &event);
              }
	break;
      }
      case ButtonPress:               // nacisniecie klawisza myszki
        button_pressed = 1; 
        if (event.xbutton.button == Button1)    // klawisz lewy
	{

	  XSetForeground(display, gc, blue);
	  
	  current_point.x = event.xbutton.x;
	  current_point.y = event.xbutton.y;
	  previous_point = current_point;
	  char lan[64];
          sprintf(lan,"lewy klawisz myszy wcisnieto w polu (%d,%d)",current_point.x,current_point.y);
          XSetForeground(display, gc, blue); 
	  XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 
			   20, 20, lan, strlen(lan));
	  /*event.type = Expose;	  
	  event.xexpose.count = 0;
	  XSendEvent(display, window, 0, ExposureMask, &event); */
	}  
	else if (event.xbutton.button == Button2)  // klawisz srodkowy
	{
          XSetForeground(display, gc, blue); 
	  XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 
			   20, 20, "srodkowy klawisz myszy wcisnieto", strlen("srodkowy klawisz myszy wcisnieto"));
        }
	else if (event.xbutton.button == Button3) // klawisz prawy
	{
	  XSetForeground(display, gc, blue);
	  XDrawImageString(event.xexpose.display, event.xexpose.window, gc, 
			   20, 20, "prawy klawisz myszy wcisnieto", strlen("prawy klawisz myszy wcisnieto"));
        } 
	break;
      case ButtonRelease:               // puszczenie klawisza myszki
        if (event.xbutton.button == Button1)    // klawisz lewy
	{
	  Vx += (current_point.x - previous_point.x)/10;
	  Vy += (current_point.y - previous_point.y)/10;
	  
	}
	event.type = Expose;	  
	event.xexpose.count = 0;
	XSendEvent(display, window, 0, ExposureMask, &event); 
	button_pressed = 0; 
	break;  
	
      
      case KeyPress:                   // wcisniecie klawisza na klawiaturze 
	hm_keys = XLookupString(&event.xkey, buffer, 8, &key, 0);
	
	if ((hm_keys == 1) && (buffer[0] == 'q'))
	  to_end = TRUE;
	if ((hm_keys == 1) && (buffer[0] == '1'))
	{
	  XWindowAttributes xwAttr;                   
          XGetWindowAttributes(display,window,&xwAttr);   // odczyt atrybutow okna           

          printf("atrybuty okna: szer = %d, wys = %d, pol = (%d, %d)\n",xwAttr.width,xwAttr.height,xwAttr.x,xwAttr.y);
        }

        break;
        
      default:
	break;
    } // switch event
    
  }
  
  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
 
  return 0;
}


