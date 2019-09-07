/* 
 * Originally by Philip Koopman (koopman@cmu.edu)
 * and Milda Zizyte (milda@cmu.edu)
 *
 * STUDENT NAME: Lavina Chandwani
 * ANDREW ID: lchandwa
 * LAST UPDATE: 2:10 AM 
 *
 * This file was originally an algorithm to solve the ece642rtle maze
 * using the left-hand rule. The code was intentionaly left obfuscated.
 * 
 * The code has been modified to use the right-hand rule. The code has
 * been cleaned up to maintain consistency and make it easy to understand.
 *
 */

#include "student.h"

// Ignore this line until project 5
turtleMove studentTurtleStep(bool bumped) {return MOVE;}

// OK TO MODIFY BELOW THIS LINE

const float TIMEOUT = 40;    // bigger number slows down simulation so you can see what's happening
float w, cs;
float fx1, fy1, fx2, fy2;
float z, aend, mod, bp, q;

enum cs_value {move_trle=2, bump_trle=1, stop_trle=0};
enum nw_or_value {LEFT=0, UP=1, RIGHT=2, DOWN=3};
		 
// this procedure takes the current turtle position and orientation and returns
// true=submit changes, false=do not submit changes
// Ground rule -- you are only allowed to call the helper functions "bumped(..)" and "atend(..)",
// and NO other turtle methods or maze methods (no peeking at the maze!)
bool studentMoveTurtle(QPointF& pos_, int& nw_or) {
    ROS_INFO("Turtle update Called  w=%f", w);
    mod = true;
    if(w == 0) {
        fx1 = pos_.x(); 
        fy1 = pos_.y();
        fx2 = pos_.x(); 
        fy2 = pos_.y();
        
	if (nw_or < 2) {
            (nw_or == 0) ? fy2+=1: fx2+=1;
        }
	else {
	    fx2+=1;
            fy2+=1; 
	    (nw_or == 2) ? fx1+=1: fy1+=1; 
        }   
       
	bp = bumped(fx1,fy1,fx2,fy2);
	aend = atend(pos_.x(), pos_.y());
        
        //Turtle orientation conditions
        //Turtle moves right at each step (very first step is in forward direction)
        //If turtle faces bump it will keep turning to its left until it finds an
        //open path
        if(nw_or == LEFT) {
	    if(cs == move_trle) {
                nw_or = UP;  
                cs = bump_trle; 
            }
	    else if (bp) {
                nw_or = DOWN;  
                cs = stop_trle; 
            }
	    else {
                cs = move_trle;
            }
        }
	else if(nw_or == UP) {
	    if(cs == move_trle) { 
                nw_or = RIGHT; 
                cs = bump_trle; 
            }
	    else if (bp) {
                nw_or = LEFT;  
                cs = stop_trle;
            }
	    else {
                cs = move_trle;
            }
        }
	else if(nw_or == RIGHT) {
	    if(cs == move_trle) { 
                nw_or = DOWN;
                cs = bump_trle;
            }
	    else if (bp) {
                nw_or = UP;
                cs = stop_trle;
            }
	    else {
                cs = move_trle;
            }
	}
	else if(nw_or == DOWN) {
	    if(cs == move_trle) { 
                nw_or = LEFT;
                cs = bump_trle; 
            }
	    else if (bp) { 
                nw_or = RIGHT;
                cs = stop_trle;
            }
	    else {
                cs = move_trle;
            }
        }

	ROS_INFO("Orientation=%f  STATE=%f", nw_or, cs);

        //whenever cs is equal to move_trle turtle moves 1 step forward
        z = (cs == move_trle);

        mod = true;
        
        //turtle movement condition, movement depends on the direction 
        //turtle is facing
	if(z == true && aend == false) {
            switch(nw_or) {
                case UP: pos_.setY(pos_.y() - 1);
                     break; 
                case RIGHT: pos_.setX(pos_.x() + 1);
                     break;
                case DOWN: pos_.setY(pos_.y() + 1);
                     break;
                case LEFT: pos_.setX(pos_.x() - 1);
                     break;
                default: break;
            }
            z = false;
            mod = true;
        }
    }
    
    //at final goal turtle stops moving
    if (aend) {
        return false;
    }

    //turtle orientation available after timeout
    (w==0)? w  = TIMEOUT: w -= 1;
    
    if (w==TIMEOUT) {
        return true;
    }

    return false;
}
