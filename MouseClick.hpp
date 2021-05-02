#ifndef MOUSECLICK_HPP
#define MOUSECLICK_HPP

#ifdef _WIN32
#include <stdlib.h>
#include <windows.h>
    #elif _WIN64
#include <stdlib.h>
#include <windows.h>
    #elif __APPLE__ || __MACH__
//#include <mach-o/dyld.h>
#include <unistd.h>
#include <ApplicationServices/ApplicationServices.h>
    #elif __linux__//https://www.linuxquestions.org/questions/programming-9/simulating-a-mouse-click-594576/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

void mouseClick(int button)
{
    Display *display = XOpenDisplay(NULL);

    XEvent event;

    if(display == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del Display !!!\n");
        exit(EXIT_FAILURE);
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");

    XFlush(display);

    usleep(100000);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");

    XFlush(display);

    XCloseDisplay(display);
}
    #elif __FreeBSD__
#include <sys/types.h>
#include <sys/sysctl.h>
    #endif
/*
 * Returns the full path to the currently running executable,
 * or an empty string in case of failure.
 */



void mouseLeftClick() {
    #ifdef _WIN32

    INPUT    Input={0};
      // left down
      Input.type      = INPUT_MOUSE;
      Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
      ::SendInput(1,&Input,sizeof(INPUT));

      // left up
      ::ZeroMemory(&Input,sizeof(INPUT));
      Input.type      = INPUT_MOUSE;
      Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
      ::SendInput(1,&Input,sizeof(INPUT));

    #elif __linux__

    mouseClick(1);//left = 1, middle = 2, right = 3, wheel up = 4, wheel down = 5 according to xdotool

    #elif __APPLE__ || __MACH__

    CGEventRef event = CGEventCreate(nil);//supposedly gets the mouse position according to https://stackoverflow.com/questions/2262516/getting-global-mouse-position-in-mac-os-x
    CGPoint loc = CGEventGetLocation(event);
    CFRelease(event);

    CGEventRef click_down = CGEventCreateMouseEvent(//https://stackoverflow.com/questions/12123150/how-to-programmatically-simulate-a-mouse-click-without-moving-mouse-in-cocoa
    	NULL, kCGEventLeftMouseDown,
    	loc,
    	kCGMouseButtonLeft
  	);

    CGEventRef click_up = CGEventCreateMouseEvent(
    	NULL, kCGEventLeftMouseUp,
    	loc,
    	kCGMouseButtonLeft
  	);

    CGEventPost(kCGHIDEventTap, click_down);
    CGEventPost(kCGHIDEventTap, click_up);

    // Release the events
    CFRelease(click_down);
    CFRelease(click_up);

    #elif __FreeBSD__



    #endif
    return;

}

void mouseRightClick() {
    #ifdef _WIN32

    INPUT    Input={0};
      // left down
      Input.type      = INPUT_MOUSE;
      Input.mi.dwFlags  = MOUSEEVENTF_RIGHTDOWN;
      ::SendInput(1,&Input,sizeof(INPUT));

      // left up
      ::ZeroMemory(&Input,sizeof(INPUT));
      Input.type      = INPUT_MOUSE;
      Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
      ::SendInput(1,&Input,sizeof(INPUT));

    #elif __linux__

    mouseClick(3);//left = 1, middle = 2, right = 3, wheel up = 4, wheel down = 5 according to xdotool

    #elif __APPLE__ || __MACH__

    CGEventRef event = CGEventCreate(nil);//supposedly gets the mouse position according to https://stackoverflow.com/questions/2262516/getting-global-mouse-position-in-mac-os-x
    CGPoint loc = CGEventGetLocation(event);
    CFRelease(event);

    CGEventRef click_down = CGEventCreateMouseEvent(
    	NULL, kCGEventRightMouseDown,
    	loc,
    	kCGMouseButtonLeft
  	);

    CGEventRef click_up = CGEventCreateMouseEvent(
    	NULL, kCGEventRightMouseUp,
    	loc,
    	kCGMouseButtonLeft
  	);

    CGEventPost(kCGHIDEventTap, click_down);
    CGEventPost(kCGHIDEventTap, click_up);

    // Release the events
    CFRelease(click_down);
    CFRelease(click_up);

    #elif __FreeBSD__



    #endif
    return;

}
#endif // MOUSECLICK_HPP
