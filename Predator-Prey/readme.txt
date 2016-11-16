Albert Chang
CS162-400
Lab 5

This isn't a formal design doc (though I did plan things out before coding)
but I still want to leave a few notes about the program.

I made a few changes after writing this out, and I noted the changes (with all caps
"DESIGN CHANGE") in the relevant area without removing my earlier thoughts about the
design.

First, here are some notes from my initial brainstorming (not cleaned up in any way):

main program:
provide a world (dynamic array) as well as a temporary world
bug functions work only on the temporary world

start by creating bugs on main array
each bug is passed both arrays as arguments
bugs never directly alter main array, only the temporary array
results are copied back from temporary array to main array at end of timestep
stuff is printed

flow of time is as follows (discrete steps):
doodle move (if they eat ants, the ant is gone at this point)
ant move
doodle breed
ant breed
doodle starve (doodle can breed before starving with great effort)

menu logic:
Loop until the number of generations has passed
at that point, produce a prompt (enter 0 to quit or a positive number to continue)

(planning notes are over)
Additional note: Doodlebugs breeding before Ants might be counterintuitive, but I wanted
to maintain the order of Doodlebug actions and Ant actions alternating. Doodlebugs being
able to breed before starving might be counterintuitive as well, but just imagine some
Disney storyline (like Bambi or Lion King): The newly born Doodlebug cries over its parent's
rapidly decaying corpse before going out to hunt the Ants that cruelly allowed its parent
to starve by not existing nearby. With discrete steps in each timestep, this means that
after movement (and eating), Ants and Doodlebugs can produce a child in a space that was
occupied pre-movement. The main result visually is that it might look like a Doodlebug is
wading through a sea of Ants if the Ants reproduce into the Doodlebug's former location.


You may notice that I didn't have much planning for the Critter functions. I thought they
would be fairly straightforward. They weren't really, but I still figured out how to
approach them. For polymorphism, the only polymorphic function I have is move(). I had
considered making other functions (mostly breeding) polymorphic as well, but while coding
I realised that there was really no need for that. Differences between Doodlebugs and
Ants could be easily represented by member variables (which I did with the species enum)
and aside from their different movement patterns (Doodlebugs attempt to move over Ants)
their behavior could be handled by identical functions (again, mostly referring to
breeding here). Having breed() as a Critter function meant I had to include the headers
for Ants and Doodlebugs in the Critter implementation file. This might be poor OOP. The
only difference though would be the "new Doodlebug" or "new Ant" at the very end of the
function, and it seems unnecessary to create two functions just to change one word. If
you think the inclusion of ant.hpp and doodlebug.hpp in the Critter implementation file
is poor form, please overlook it this time and pretend I had properly used polymorphic
functions to handle breeding. (The constants for breeding and starving time are in the
Critter header for the same reason.)

DESIGN CHANGE: After writing this short explanation, I decided to go back and make
breed() a polymorphic function with a pure virtual breed() in Critter.
I still think this is inefficient from a coding standpoint (having nearly identical
functions for the two derived classes), but I thought about OOP some more and I believe
that Critter shouldn't have functions that are dependent on its derived classes.
(end of DESIGN CHANGE)

I have many member functions in the Critter class (probably many more than would be
expected) but they were each made with a purpose to make implementation easier. The end
result is that Ant and Doodlebug only have one unique member function each (for movement)
and they can call the Critter functions for anything else they need. The species variable
was already mentioned earlier, but this variable (and the getSpecies() function) allow
the species of each Critter to be easily obtained without having to use casting. I think
this is a simpler solution, though it also shows that I still have no experience with
properly using dynamic casting. I hope this is okay with you. 

dying() and getDyingFlag() are fairly straightfoward functions. One of them marks the
Critter as dying, and the other retrieves the flag for other functions to check. dying()
takes no parameters because the act of dying is not a reversible process, and there's no
method to change the dying flag from true back to false. These bugs don't get miracles.

The four functions for checking cell occupancy (that are named "empty" or "occupied")
are used in different ways. It's probably obvious that the "temp" functions check the
temporary world, and the non-"temp" functions check the real world. Empty and occupied
are different because both functions also check for borders in deciding what boolean
value to return. You can see that with the consideration of borders, a lack of emptiness
doesn't indicate occupancy, and a lack of occupancy doesn't indicate emptiness. So I made
two sets of functions for whether I need to check for empty cells or occupied cells. This
is mainly relevant for Doodlebug feeding, because they want to eat into an occupied cell
(occupied by Ant) but regular movement is done by searching for empty cells. One of the
four (tempIsOccupied) is never even used, but it didn't seem right to leave it out just
because I didn't need it. The functions come in a set.

Doodlebugs have two unique member variables for checking whether they succeeded in eating
and whether they failed to eat for too long. I have these as Doodlebug variables because
they aren't relevant to Ants.

I added a "bias fix" variable after finishing up to try to reduce the bias for the upper
left side of the board compared to when using "rand() % 2" for a simple binary yes/no
option. I reduce the bias fix by 1 each time through the loop (the outer loop) because
I figured that if the bug placement wasn't done in one whole pass through the array, then
the chance of being placed (reflected in a lower modulus, down to 1 for 100% placement)
should increase with each pass through the loop. Though I'm not sure this is a great way
to handle a fair distribution, it passes the eye test when I tried placing different
amounts of Ants and Doodlebugs onto a larger world.

I also added destructors for Critter, Ant, and Doodlebug (with nothing in the body of the
functions, because I don't actually want to destroy the dynamic worlds that each Critter
has pointers to) because I got a warning from the compiler that deleting an abstract
class with a non-virtual destructor could have undefined behavior. I read up on this
online (doesn't seem to be in our book yet) and I think this is necessary when using base
class (Critter) pointers to derived classes (Ant and Doodlebug). I think the extra member
variables of Ant and Doodlebug (just Doodlebug because Ant has no unique variables) might
not be destroyed properly without a virtual destructor, even though there's no removal of
dynamically allocated variables happening. Compiling on the school server doesn't give
this warning, but I'm using a newer version of g++ and I assume the newer version has
more warnings for a reason.

In the main function, the "engine" functions are only ever called on the real world
(the "overworld" in my code) to avoid accidentally performing actions on newly born bugs
right after they're born. That doesn't break the program, but stuff gets weird and the
pattern becomes inconsistent. The temporary world (underworld) is copied back after
movement because all movement occurs before all breeding. Also note that movement checks
both the temporary world and the current world to help provide the illusion of
simultaneous movement. The idea is that a bug can't move to a spot that was occupied at
the beginning of the step, even if the bug has moved out of that spot by the end of the
step. They can only move to spots that were empty at the start of the timestep. (The
exception of course is that Ants can move into spots Doodlebugs occupied at the beginning
of the step, because all Doodlebugs always move before all Ants).

The rest of the code is fairly straightforward, so there isn't much else to say. The
program displays the initial state if told to run for 0 steps initially, but any further
attempts to run for 0 steps will just quit the program. I only mention this because I can
see how it might seem like an oversight, but it's by design and not an oversight. It can
be easily changed (with a simple "for" loop), but I thought 0 should quit the program
because there's no point in making the program redraw the exact same board. 0 is only
allowed for the very first input because it could be helpful for checking the initial
board state. I used this for determining whether my "bias fix" was acceptable.

