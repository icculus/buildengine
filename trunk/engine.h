/*
 * A list of all symbols exported from engine.c for a game's use.
 *
 *  Put together by Ryan C. Gordon (icculus@clutteredmind.org)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */

/**@file engine.h
 * @brief Main engine include file.
 *
 * A list of all symbols exported from engine.c for a game's use.
 */

#ifndef _INCLUDE_ENGINE_H_
#define _INCLUDE_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SUPERBUILD  /* don't touch this. */

/*
 * this must be implemented by every program that uses the BUILD engine.
 *  engine.c calls this function in several places.
 *  See Ken's test game (in game.c), and his editor (in bstub.c) for examples.
 */
void faketimerhandler(void);

/*
 * exported engine functions, in absolutely no particular order.
 *  See build.txt, build2.txt...and anything else with a .txt extention for
 *  information on using these functions that may or may not be accurate. :)
 */
int initmouse(void);

/**@brief Set the video mode.
 *
 * This function sets the video mode.
 * If you change the mode in your program,
 * you must call this again to reset the mode 
 * before using the build drawing functions.
 * @param davidoption The video modeset to use (0-6).
 * Allowed options:
 * @arg \c 0 -- 
 * @arg \c 1 -- VESA mode. Any VESA resolution is allowed.
 * @arg \c 2 -- 
 * @arg \c 3 -- 
 * @arg \c 4 -- 
 * @arg \c 5 -- 
 * @arg \c 6 -- 
 * @param daxdim The x resolution. (must be 320 if param 1 != 1.)
 * @param daydim The y resolution. (must be 200 if param 1 != 1.)
 */
int setgamemode(char davidoption, long daxdim, long daydim);

/**@brief Get the ceiling z value for a point in a sector.
 *
 * This function returns the Z value of a ceiling at a point in the sector.
 * @param sectnum The sector to look in.
 * @param dax The x coordinate to look in.
 * @param day The y coordinate to look in.
 * @return The z coordinate at that point.
 */
int getceilzofslope(short sectnum, long dax, long day);

/**@brief Get the floor z value for a point in a sector.
 *
 * This function returns the Z value of a floor at a point in the sector.
 * @param sectnum The sector to look in.
 * @param dax The x coordinate to look in.
 * @param day The y coordinate to look in.
 * @return The z coordinate.
 */
int getflorzofslope(short sectnum, long dax, long day);

/**@brief Get the floor and ceiling z values for a point.
 *
 * This function finds the Z value of a floor and ceiling,
 * and stores the values in two pointers.
 * @param sectnum The sector to look in.
 * @param dax The x coordinate to look in.
 * @param day The y coordinate to look in.
 * @param *ceilz A pointer to write the ceiling z value to.
 * @param *florz A pointer to write the floor z value to.
 */
void getzsofslope(short sectnum, long dax, long day, long *ceilz, long *florz);

/**@brief Set aspect ratio and viewing range angle.
 *
 * This function sets the aspect ratio
 * and viewing range angle of the engine.
 * Used for weird video modes or special effects.
 * @param daxrange Sets the viewing range angle.
 * @param daaspect Sets the aspect ratio.
 * @remark Ken's Notes on this function:
 * \n---------------------\n
 * For a standard 90ø 320*200 screen, daxrange and daaspect are
 * 65536.  For square aspect ratio at 320*400, set daaspect
 * to 131072.  Since daxrange is actually zoom, you must
 * modify the aspect ratio inversely if you only want to
 * change the viewing angle.
 * \n---------------------\n
 * [for daaspect] you pass the Y/X aspect ratio scaled up 16 bits, so
 * 65536 would be normal.  You don't need to call this if you
 * don't want to.  By default, in setview, I call setaspect
 * with these parameters:
 * setaspect(divscale16(ydim*320,xdim*200));
 * (also written as:)
 * setaspect(((ydim*320)<<16)/(xdim*200));
 * Note that in 320*200 mode the value passed would be 65536
 * which is a 1:1 aspect ratio.
 * \n---------------------\n
 * Since drawmapview is also affect by the aspect ratio, you
 * will need to make sure drawoverheadmap is affected so
 * the map modes match up.  Please look at and copy my updated
 * drawoverheadmap function into your GAME.C if you use it.
 *
 */
void setaspect(long daxrange, long daaspect);

/**@brief Insert a sprite into a sector.
 *
 * This function is used to insert a sprite into a sector.
 * @param sectnum The sector number to place the sprite into.
 * @param statnum The sprite's status. (cstat)
 * @return The number assigned to the new sprite.
 */
int insertsprite(short sectnum, short statnum);

/**@brief Update a sector pointer, given x and y values.
 *
 * This function updates a pointer with the sector number
 * occupied by an x and y value.
 * @param x The x coordinate to look up.
 * @param y The y coordinate to look up.
 * @param *sectnum A pointer to the variable you want to
 * write the result into.
 * @remark Ken's Notes on this function:
 * \n Be careful when you use this function with sprites because
 * remember that the sprite's sector number should not be modified directly.
 * If you want to update a sprite's sector, I recommend using the setsprite
 * function.
 *
 */
void updatesector(long x, long y, short *sectnum);

/**@brief Find the wall to the left of another wall.
 *
 * Use this function as a reverse function of wall[].point2.
 * @param point The wall to search with.
 * @return The wall to the left of \a point.
 */
int lastwall(short point);

/**@brief Set up the sprite lists.
 *
 * This function will initialize the doubly-linked
 * sprite sector and sprite status lists.
 */
void initspritelists(void);

/**@brief Delete a sprite from the map.
 *
 * This function will delete a sprite.
 * @param spritenum The sprite number to delete.
 */
int deletesprite(short spritenum);
int insertspritesect(short sectnum);
int deletespritesect(short deleteme);
int deletespritestat (short deleteme);
int insertspritestat(short statnum);
int changespritesect(short spritenum, short newsectnum);
int changespritestat(short spritenum, short newstatnum);
/**@brief Loads a tile into memory
 *
 * This function will ensure \a tilenume is in memory.
 * @param tilenume The tile to load.
 * @remark Ken's Notes on this function:
 * \n A tile is not in the cache if (waloff[tilenum] == 0)
 *
 */
void loadtile(short tilenume);
void setmmxoverlay(int isenabled);
int getmmxoverlay(void);

/**@brief Flip to next drawing page.
 *
 * This function flips to the next drawing page. After a page is prepared,
 * use this function to show the it on the screen and set up the next
 * one for drawing.
 *
 */
void nextpage(void);

/**@brief Draw the 3D screen to the current drawing page.
 *
 * This function draws the current 3D screen to the current
 * drawing page. Remember to call \a nextpage() to actually
 * show the page on the screen!
 * @param daposx X position of the camera.
 * @param daposy Y position of the camera.
 * @param daposz Z position of the camera.
 * @param daang Viewing angle of the camera.
 * @param dahoriz ??? fixme
 * @param dacursectnum Sector camera is currently in.
 */
void drawrooms(long daposx, long daposy, long daposz,
               short daang, long dahoriz, short dacursectnum);

/**@brief Loads a map from disk.
 *
 * This function loads a map from disk and stores the starting
 * location in the pointers you pass.
 * If no extention is given to \a filename, .MAP is assumed.
 * @param filename The filename to load.
 * @param *daposx A pointer for the starting X coordinate.
 * @param *daposy A pointer for the starting Y coordinate.
 * @param *daposz A pointer for the starting Z coordinate.
 * @param *daang  A pointer for the starting angle.
 * @param *dacursectnum A pointer for the starting sector.
 * @return -1 if the map is not found.
 */
int loadboard(char *filename, long *daposx, long *daposy,
			  long *daposz, short *daang, short *dacursectnum);

/**@brief Draw the sprites and maskwalls to the current drawing page.
 *
 * This function will draw the visible sprites and masked walls
 * to the current drawing page.
 * @remark Ken's Notes on this function:
 * \n This function draws all the sprites and masked walls to the current
 * drawing page which is not yet shown. The reason I have the drawing
 * split up into these 2 routines is so you can animate just the
 * sprites that are about to be drawn instead of having to animate
 * all the sprites on the whole board. Drawrooms() prepares these
 * variables: spritex[], spritey[], spritepicnum[], thesprite[],
 * and spritesortcnt. Spritesortcnt is the number of sprites about
 * to be drawn to the page. To change the sprite's picnum, simply
 * modify the spritepicnum array If you want to change other parts
 * of the sprite structure, then you can use the thesprite array to
 * get an index to the actual sprite number.
 */
void drawmasks(void);

/**@brief Draws a text message to the screen.
 *
 * This function will draw a message to the screen
 * using one of the built in fonts.
 * @param xpos X position of text.
 * @param ypos Y position of text.
 * @param col Color of text.
 * @param backcol Background color of text, or -1 for transparency.
 * @param name The text to draw.
 * @param fontsize The font size. Legal values: 0 -- 8x8 font. 1 -- 4x6 font.
 */
void printext256(long xpos, long ypos, short col, short backcol,
			char name[82], char fontsize);

/**@brief Draws a text message to the screen without refreshing.
 *
 * This function will draw a message to the screen
 * using one of the built in fonts.
 * It will also avoid refreshing the screen. See Ryan's notes below.
 * @param xpos X position of text.
 * @param ypos Y position of text.
 * @param col Color of text.
 * @param backcol Background color of text, or -1 for transparency.
 * @param name The text to draw.
 * @param fontsize The font size. Legal values: 0 -- 8x8 font. 1 -- 4x6 font.
 * @remark Ryan's notes on this function:
 * \n This is ryan's change. SDL requires me to call SDL_UpdateRect() to force
 * vid updates without a SDL_Flip() call, but there's no such thing in the
 * DOS version of this program, so text won't show up sometimes without
 * my update call in Linux. \n However, to get a nice shadow effect on some
 * text, Ken draws a string at an offset and darker, and then on top of it
 * draws the actual string. \n Two SDL_UpdateRect() calls in over top of each
 * other cause flicker, so I have this function here so the shadow can
 * be drawn with _noupdate, and the actual string is draw with an update.
 */
void printext256_noupdate(long xpos, long ypos, short col, short backcol,
			char name[82], char fontsize);

/**@brief Initialize the Build Engine.
 *
 * This function initializes many variables for the Build Engine.
 * You should call this function before using any other Build functions.
 */
void initengine(void);

/**@brief Uninitialize the Build Engine.
 *
 * This function frees the buffers used by the build engine.
 * You should call this function once before you end your program.
 */
void uninitengine(void);

/**@brief Loads an artwork file into the engine.
 *
 * This function is used to load an artwork file into memory
 * so the engine knows where to find the tiles
 * referenced by the artwork file.
 * If no extention is given to \a filename, .ART is assumed.
 * @param *filename The name of the artwork file.
 * @return -1 if the file was not found.
 */
int loadpics(char *filename);

/**@brief Saves a map to disk.
 *
 * This function dumps the working map to disk,
 * using the pointers you pass as the starting location.
 * If no extention is given to \a filename, .MAP is assumed.
 * @param filename The filename to save.
 * @param *daposx A pointer containing the starting X coordinate.
 * @param *daposy A pointer containing the starting Y coordinate.
 * @param *daposz A pointer containing the starting Z coordinate.
 * @param *daang  A pointer containing the starting angle.
 * @param *dacursectnum A pointer containing the starting sector.
 */
int saveboard(char *filename, long *daposx, long *daposy, long *daposz,
                         short *daang, short *dacursectnum);

/**@brief Plots a pixel to the screen.
 *
 * This function can plot a pixel to the screen
 * in any graphics mode. \n
 * NOTE: This function is not designed to be fast! 
 * Use it in moderation.
 * @param x The x coordinate of the pixel.
 * @param y The y coordinate of the pixel.
 * @param col The color of the pixel.
 */
void plotpixel(long x, long y, char col);

/**@brief Returns the color of a pixel on screen.
 *
 * This function will find the color of a pixel
 * in any graphics mode. \n
 * NOTE: This function is not designed to be fast!
 *  -- Use it in moderation.
 * @param x The x cordinate of the pixel.
 * @param y The y coordinate of the pixel.
 * @return The color of the pixel.
 */
unsigned char getpixel(long x, long y);

/**@brief Adjust the gamma of a VGA palette.
 *
 * This function will adjust the brightness of colors in \a dapal.
 * @param dabrightness The gamma level. Accepted range of 0-15,
 * where 0 is the darkest and 15 is the lightest.
 * @param *dapal A pointer to a standard 768 byte VGA palette.
 */
void setbrightness(char dabrightness, unsigned char *dapal);

/**@brief Take a screenshot.
 *
 * This function will dump a picture of the current screen
 * to a file. \n
 * Set \a inverseit to 1 if you want the colors inverted.
 * @param *filename The filename to write to.
 * @param inverseit Set to 1 if you want the colors inverted.
 * @remark Notes on \a filename:
 * \n If you use "captxxxx.pcx" as your filename,
 * Build will automatically replace the x's with
 * an automatically incrementing number, starting
 * from 0000.
 */
int screencapture(char *filename, char inverseit);

/**@brief Get the current mouse location and button state.
 *
 * This function will store the current mouse position and
 * the state of the mouse buttons in the pointers you give it.
 * @param mousx A pointer to write the X position of the mouse to.
 * @param mousy A pointer to write the Y position of the mouse to.
 * @param bstatus A pointer to write the current state of the mouse buttons to.
 * @remark \a bstatus is a bitmask of the mouse states:
 * @arg 1 -- Left button is down.
 * @arg 2 -- Right button is down.
 * @arg 4 -- Middle button is down. 
 */
void getmousevalues(short *mousx, short *mousy, short *bstatus);

/**@brief Move an object using collision detection.
 *
 * This function will move any object at any velocity
 * and make sure the object stays a certain distance from walls.
 * @param *x A pointer to the object's X coordinate.
 * @param *y A pointer to the object's Y coordinate.
 * @param *z A pointer to the object's Z coordinate.
 * @param *sectnum A pointer to the object's current sector.
 * @param xvect The desired X velocity of movement.
 * @param yvect The desired Y velocity of movement.
 * @param walldist The distance the object should stay away from walls.
 * @param ceildist The distance the object should stay away from the ceiling.
 * @param flordist The distance the object should stay away from the floor.
 * @param cliptype See description below.
 * @return Status of clipping:
 * @arg 0 -- Nothing was touched.
 * @arg 32768+wallnum -- Wall first touched.
 * @arg 49152+wallnum -- Sprite first touched.
 * @remark Notes on this function:
 * \n xvect and yvect are calculated with the following equations:
 * @arg xvect = velocity * cos(angle)
 * @arg yvect = velocity * sin(angle)
 * @remark Ken uses 128 for walldist as his default.
 * \n Don't suddenly increase walldist -- it may cause an object to go
 * throught the wall!
 * \n Cliptype is a mask that tells whether the object should be clipped
 * to or not. \n The lower 16 bits are anded with wall[].cstat and the higher
 * 16 bits are anded with sprite[].cstat.
 */
int clipmove (long *x, long *y, long *z, short *sectnum, long xvect,
			long yvect, long walldist, long ceildist,
			long flordist, unsigned long cliptype);

/**@brief Find the highest and lowest z coordinates your clipping box can get to.
 *
 * This function finds the highest and lowest z coordinates your clipping box can get to.
 * @param x X coordinate of location.
 * @param y Y coordinate of location.
 * @param z Z coordinate of location.
 * @param sectnum Current sector.
 * @param *ceilz Pointer to store Z extent of ceiling.
 * @param *florz Pointer to store Z extent of floor.
 * @param *ceilhit First object hit in the up direction.
 * @param *florhit First object hit in the down direction.
 * @param walldist Size of your clipping box.
 * @param cliptype See description below.
 * @remark Notes on this function: \n
 * \a walldist is suggested to be 128. \n
 * \a ceilhit and \a florhit will be the following after the function call: \n
 * 16384+sector (sector first touched) or \n
 * 49152+spritenum (sprite first touched)
 */
void getzrange(long x, long y, long z, short sectnum,
			long *ceilz, long *ceilhit, long *florz, long *florhit,
			long walldist, unsigned long cliptype);

/**@brief Gets the angle of a vector.
 *
 * This function will return the angle closest to the
 * vector you specify. \n
 * There are 2048 possible angles, starting from the right (3 o'clock), going clockwise.
 * @param xvect The x component.
 * @param yvect The y component.
 */
int getangle(long xvect, long yvect);

/**@brief Adjust the slope of a sector's ceiling to pass through a point
 *
 * This function will cause the slope of a sector to change
 * and the sector plane to pass through the point specified.
 * @param dasect The sector to modify.
 * @param x The X coordinate to intersect.
 * @param y The Y coordinate to intersect.
 * @param z The Z coordinate to intersect.
 * @remark Given a sector and assuming it's first wall
 * is the pivot wall of the slope,
 * this function makes the slope pass through the x,y,z point.
 */
void alignceilslope(short dasect, long x, long y, long z);

/**@brief Adjust the slope of a sector's floor to pass through a point
 *
 * This function will cause the slope of a sector to change
 * and the sector plane to pass through the point specified.
 * @param dasect The sector to modify.
 * @param x The X coordinate to intersect.
 * @param y The Y coordinate to intersect.
 * @param z The Z coordinate to intersect.
 * @remark Given a sector and assuming it's first wall
 * is the pivot wall of the slope,
 * this function makes the slope pass through the x,y,z point. \n
 * One use of this function is sine-wave floors.
 */
void alignflorslope(short dasect, long x, long y, long z);

/**@brief Project a ray and report what it hit.
 *
 * This function will project a ray in the direction
 * specified by a 3D vector
 * and report where and what the ray hit.
 * @param xs Starting X position.
 * @param ys Starting Y position.
 * @param zs Starting Z position.
 * @param sectnum Starting sector.
 * @param vx X component of 3D vector.
 * @param vy Y component of 3D vector.
 * @param vz Z component of 3D vector.
 * @param *hitsect The sector that the intersection occured in.
 * @param *hitwall The wall that got hit.
 * @param *hitsprite The sprite that got hit.
 * @param *hitx The X coordinate of the point that the intersection occured.
 * @param *hity The Y coordinate of the point that the intersection occured.
 * @param *hitz The Z coordinate of the point that the intersection occured.
 * @param cliptype See description below.
 * @remark Notes on this function: \n
 * HOW TO DETERMINE WHAT WAS HIT:\n
 * If the ray hits a sprite, then
 * @arg hitsprite = thespritenumber.
 * @arg hitwall = -1.
 * @remark If the ray hits a wall, then
 * @arg hitsprite = -1
 * @arg hitwall = thewallnumber
 * @remark If the ray hits the ceiling of a sector, then
 * @arg hitsprite = -1
 * @arg hitwall = -1
 * @arg vectorz < 0
 * @arg (If vectorz < 0 then you're shooting upward which means
 * that you couldn't have hit a floor)
 * @remark If the ray hits the floor of a sector, then
 * @arg hitsprite = -1
 * @arg hitwall = -1
 * @arg vectorz > 0
 * @arg (If vectorz > 0 then you're shooting downard which means
 * that you couldn't have hit a ceiling)
 */
int hitscan(long xs, long ys, long zs, short sectnum,
            long vx, long vy, long vz,
	        short *hitsect, short *hitwall, short *hitsprite,
	        long *hitx, long *hity, long *hitz, unsigned long cliptype);

/**@brief Tests to see if a 2d point is in a sector.
 *
 * This function will check if a 2d point is inside a sector.
 * @param x X coordinate of point.
 * @param y Y coordinate of point.
 * @param sectnum The sector to test against.
 */
int inside (long x, long y, short sectnum);

/**@brief Sets the first wall of a sector.
 *
 * This function sets the first wall of a sector.
 * It can be used to change the hinge wall of a slope,
 * among other things.
 * @param sectnum The sector to modify.
 * @param newfirstwall The wall to set as the first wall.
 */
void setfirstwall(short sectnum, short newfirstwall);

/**@brief Rotate / translate a point.
 *
 * This function is a very convenient and fast math helper function.
 * Rotate points easily with this function without having to juggle your
 * cosines and sines.
 * @param xpivot X coordinate of point to pivot about.
 * @param ypivot Y coordinate of point to pivot about.
 * @param x X coordinate of point to translate.
 * @param y Y coordinate of point to translate.
 * @param daang Angle to rotate (CW, relative)
 * @param *x2 X coordinate of the translated point.
 * @param *y2 Y coordinate of the translated point.
 */
void rotatepoint(long xpivot, long ypivot, long x, long y, short daang,
			long *x2, long *y2);

/**@brief Draw the tile screen.
 *
 * This function draws the tile chooser in Build.
 * (what you get when you press "v".)
 * @param pictopleft The first tile to show.
 * @param picbox The tile to highlight.
 */
int drawtilescreen(long pictopleft, long picbox);

/**@brief Clear the current video page to a given color.
 *
 * This function clears the current video page to the color \a dacol.
 * @param dacol The color to clear to.
 */
void clearview(long dacol);

/**@brief Clear all video pages to a given color.
 *
 * This function clears all the video pages to the color \a dacol.
 * @param dacol The color to clear to.
 */
void clearallviews(long dacol);

/**@brief Draw a 2D grid.
 *
 * This function is used by Build to draw the grid in 2D. \n
 * NOTE: This function works only in two graphics modes: \n
 * 640*350*16col, 640*480*16col.
 * @param posxe Left side of visible grid.
 * @param posye Top side of visible grid.
 * @param ange Not used.
 * @param zoome Zoom factor of grid.
 * @param gride The grid's scale.
 * @remark Please do not use this function. It is only public
 * because the build editor needs it.
 */
void draw2dgrid(long posxe, long posye, short ange, long zoome,
			short gride);

/**@brief Draw the 2D screen.
 *
 * Thus function is used by build to draw the 2d screen. \n
 * See draw2dgrid for explanation.
 * @remark Please do not use this function. It is only public
 * because the build editor needs it.
 */
void draw2dscreen(long posxe, long posye, short ange, long zoome,
			short gride);

/**@brief A fast routine to find the sector that owns a certain wall.
 *
 * This function will find the sector that owns the wall \a theline.
 * @param theline The wall to lookup.
 * @return The sector the wall belongs to.
 */
int sectorofwall(short theline);

/**@brief Puts a sprite somewhere, without checking for validity.
 *
 * This function will move a sprite to anywhere on the map,
 * regardless of whether the new place is valid.
 * @param spritenum The sprite to move.
 * @param newx The X coordinate to move to.
 * @param newy The Y coordinate to move to.
 * @param newz The Z coordinate to move to.
 */
int setsprite(short spritenum, long newx, long newy, long newz);

/**@brief Drag a wall to a new point.
 *
 * This function will reliabaly drag a point to a new location
 * on the map, using a method identical to dragging the point in 2D edit mode.
 * @param pointhighlight The wall to drag.
 * @param dax The X coordinate to drag to.
 * @param day The Y coordinate to drag to.
 * @remark Ken's Notes about this function:
 * Every wall of course has 2 points. When you
 * pass a wall number to this function, you are actually passing 1 point,
 * the left side of the wall (given that you are in the sector of that wall)
 * Got it?
 */
void dragpoint(short pointhighlight, long dax, long day);

/**@brief Integer Square Root Function
 *
 * This function will return an integer approximating
 * the square root of a number.
 * @param num The number to work on.
 * @return The square root of \a num.
 */
int ksqrt(long num);

/**@brief Find number of walls in sector, up to a known wall.
 *
 * This function will find the number of walls in a sector,
 * up to the specified wall.
 * @param sectnum The sector to work on.
 * @param wallnum The wall to stop on.
 * @return The number of walls in \a sectnum before \a wallnum,
 * or -1 if \a wallnum does not occur in \a sectnum.
 */
int loopnumofsector(short sectnum, short wallnum);

/**@brief Check if two points can see each other.
 *
 * This function will determine whether there is a line
 * of sight between two points.
 * @param x1 X coordinate of point 1.
 * @param y1 Y coordinate of point 1.
 * @param z1 Z coordinate of point 1.
 * @param sect1 Point 1's sector.
 * @param x2 X coordinate of point 2.
 * @param y2 Y coordinate of point 2.
 * @param z2 Z coordinate of point 2.
 * @param sect2 Point 2's sector.
 */
int cansee(long x1, long y1, long z1, short sect1,
            long x2, long y2, long z2, short sect2);
int lintersect(long x1, long y1, long z1, long x2, long y2, long z2,
               long x3, long y3, long x4, long y4, long *intx,
               long *inty, long *intz);
int rintersect(long x1, long y1, long z1, long vx, long vy, long vz,
               long x3, long y3, long x4, long y4, long *intx,
               long *inty, long *intz);

/**@brief Allocate a tile permanently.
 *
 * This function allocates a place on the cache as permanent.
 * @param tilenume The tile number to associate with the memory.
 * @param xsiz The width to allocate.
 * @param ysiz The height to allocate.
 * @remark Ken's Notes on this function: \n
 * Right now, I reset the cache every time you call this
 * function so I would recommend calling this function
 * right after loadpics.
 */
int allocatepermanenttile(short tilenume, long xsiz, long ysiz);

/**@brief Draw a line.
 *
 * This function draws a colored, solid line.
 * @param x1 X coordinate of starting point.
 * @param y1 Y coordinate of starting point.
 * @param x2 X coordinate of ending point.
 * @param y2 Y coordinate of ending point.
 * @param col Color to use.
 */
void drawline256 (long x1, long y1, long x2, long y2, unsigned char col);

/**@brief Copy a piece of a tile to another tile, skipping transparent pixels.
 *
 * This function will copy a piece of \a tilenume1 into \a tilenume2,
 * skipping transparent parts. If the source coordinates are larger
 * than the source tile, the texture will automatically wrap around. \n
 * NOTE: IF THE MODIFIED TILE GETS REMOVED FROM THE CACHE,
 * \a tilenume2 WILL BE RESET TO ITS ORIGINAL FORM. \n
 * IF YOU NEED TO KEEP THE TILE CREATED BY THIS FUNCTION,
 * CALL \a allocatepermanenttile ON IT FIRST!
 * @param tilenume1 The source tile
 * @param sx1 X coordinate to start the copy from
 * @param sy1 Y coordinate to start the copy from.
 * @param xsiz The width to copy from the source.
 * @param ysiz The height to copy from the source.
 * @param tilenume2 The destination tile.
 * @param sx2 The X coordinate to paste at.
 * @param sy2 The Y coordinate to paste at.
 */
void copytilepiece(long tilenume1, long sx1, long sy1, long xsiz, long ysiz,
                   long tilenume2, long sx2, long sy2);

/**@brief Find the next closest ceiling or floor in surrounding sectors.
 *
 * This function will find the next closest ceiling or floor in the sectors surrounding
 * the given sector. It is useful for calculating where elevators
 * should stop.
 * @param sectnum The sector to test with
 * @param thez The z coordinate to start the search from.
 * @param topbottom Search ceilings/floors only.
 * @param direction Search up/down.
 * @remark Notes: \n
 * \a topbottom: pass -1 to search ceilings, 1 to search floors. \n
 * \a direction: pass -1 to search upwards, 1 to search downwards.
 */
int nextsectorneighborz(short sectnum, long thez,
                        short topbottom, short direction);

/**@brief Find the closest objects with tags the player is pointing at.
 *
 * This function will get the nearest tagged objects. It is useful for door
 * and switch activation code, among other things.
 * @param xs X coordinate to search from.
 * @param ys Y coordinate to search from.
 * @param zs Z coordinate to search from.
 * @param sectnum Sector number to search from.
 * @param ange Angle to search from.
 * @param *neartagsector The nearest tagged sector.
 * @param *neartagwall The nearest tagged wall.
 * @param *neartagsprite The nearest tagged sprite.
 * @param *neartaghitdist Distance to the found object.
 * @param neartagrange Maximum distance to search.
 * @param tagsearch What to search for.
 * @remark Notes on this function: \n
 * For \a tagsearch:
 * @arg 1 = search lotag only.
 * @arg 2 = search hitag only.
 * @arg 3 = search both lotag and hitag.
 */
int neartag(long xs, long ys, long zs, short sectnum, short ange,
            short *neartagsector, short *neartagwall, short *neartagsprite,
            long *neartaghitdist, long neartagrange, char tagsearch);

/**@brief Try to keep object away from wall.
 *
 * This function checks if an object is too close to a wall.
 * If it is, it attempts to push it away.
 * If it tries to push 256 times, and the object is still too close,
 * it returns -1.
 * @param *x Object's X coordinate.
 * @param *y Object's Y coordinate.
 * @param *z Object's Z coordinate.
 * @param *sectnum Object's sector.
 * @param walldist Distance to avoid walls by.
 * @param ceildist Distance to avoid ceilings by.
 * @param flordist Distane to avoid floors by.
 * @param cliptype See below.
 * @remark Notes on this function: \n
 * Cliptype is a mask that tells whether the object should be clipped
 * to or not. The lower 16 bits are anded with wall[].cstat and the higher
 * 16 bits are anded with sprite[].cstat.
 */
int pushmove(long *x, long *y, long *z, short *sectnum,
             long walldist, long ceildist, long flordist,
             unsigned long cliptype);

/**@brief Returns a random number.
 *
 * This function returns a pseudorandom number in the range 0-65535.
 * @return A random number.
 */
int krand(void);
void flushperms(void);

/**@brief Rotate and draw a sprite on the screen.
 *
 * This function will rotate and draw a sprite onto the screen.
 * See notes for proper usage.
 * @param sx X center of sprite to draw.
 * @param sy Y center of sprite to draw.
 * @param z Zoom to draw with.
 * @param a Angle to draw at.
 * @param picnum The tile to draw.
 * @param dashade The shade to draw with.
 * @param dapalnum The palette to draw with.
 * @param dastat Drawing options.
 * @param cx1 Upper left of screen clipping box X.
 * @param cy1 Upper left of screen clipping box Y.
 * @param cx2 Lower right of screen clipping box X.
 * @param cy2 Lower right of screen clipping box Y.
 * @remark Ken's Notes on this function.
 * @arg (sx, sy) is the center of the sprite to draw defined as
 * screen coordinates shifted up by 16.
 * @arg (z) is the zoom. Normal zoom is 65536.
 * Ex: 131072 is zoomed in 2X and 32768 is zoomed out 2X.
 * @arg (a) is the angle (0 is straight up)
 * @arg (picnum) is the tile number
 * @arg (dashade) is 0 normally but can be any standard shade up to 31 or 63.
 * @arg (dapalnum) can be from 0-255.
 * @arg if ((dastat&1) == 0) - no transluscence
 * @arg if ((dastat&1) != 0) - transluscence
 * @arg if ((dastat&2) == 0) - don't scale to setview's viewing window
 * @arg if ((dastat&2) != 0) - scale to setview's viewing window (windowx1,etc.)
 * @arg if ((dastat&4) == 0) - nuttin' special
 * @arg if ((dastat&4) != 0) - y-flip image
 * @arg if ((dastat&8) == 0) - clip to startumost/startdmost
 * @arg if ((dastat&8) != 0) - don't clip to startumost/startdmost
 * @arg if ((dastat&16) == 0) - use Editart center as point passed
 * @arg if ((dastat&16) != 0) - force point passed to be top-left corner
 * @arg if ((dastat&32) == 0) - nuttin' special
 * @arg if ((dastat&32) != 0) - use reverse transluscence
 * @arg if ((dastat&64) == 0) - masked drawing (check 255's) (slower)
 * @arg if ((dastat&64) != 0) - draw everything (don't check 255's) (faster)
 * @arg if ((dastat&128) == 0) - nuttin' special
 * @arg if ((dastat&128) != 0) - automatically draw to all video pages
 * @remark Note: As a special case, if both ((dastat&2) != 0) and ((dastat&8) != 0)
 * then rotatesprite will scale to the full screen (0,0,xdim-1,ydim-1)
 * rather than setview's viewing window. (windowx1,windowy1,etc.)
 * This case is useful for status bars, etc.\n \n
 * Ex: rotatesprite(160L<<16,100L<<16,65536,totalclock<<4,
 * DEMOSIGN,2,50L,50L,270L,150L);
 * This example will draw the DEMOSIGN tile in the center of the
 * screen and rotate about once per second.
 * The sprite will only get drawn inside the rectangle from (50,50) to (270,150).
 */
void rotatesprite(long sx, long sy, long z, short a, short picnum,
                  signed char dashade, char dapalnum, char dastat,
                  long cx1, long cy1, long cx2, long cy2);
/**@brief Make a lookup table for remapping.
 *
 * Ken's description of this function:
 * This function allows different shirt colors for sprites.
 * First prepare \a remapbuf, which is a 256 byte buffer of chars
 * with the colors to remap. \n
 * Palnum can be anywhere from 1-15. \n
 * Since 0 is where the normal palette is stored, it is a bad
 * idea to call this function with palnum=0. \n
 * In BUILD.H notice I added a new variable, spritepal[MAXSPRITES]. \n
 * Usually the value of this is 0 for the default palette. \n
 * But if you change it to the palnum in the code between
 * drawrooms() and drawmasks then the sprite will be drawn
 * with that remapped palette. \n
 * The last 3 parameters are the color that the palette fades to
 * as you get further away. \n
 * This color is normally black (0,0,0). \n White would be (63,63,63). \n
 * if ((dastat&1) == 0) then makepalookup will allocate & deallocate
 * the memory block for use but will not waste the time creating a palookup
 * table (it assumes you will create one yourself).
 */
void makepalookup(long palnum, char *remapbuf, signed char r,
                  signed char g, signed char b, char dastat);

/**@brief Draw the overhead textured map view.
 *
 * This function is used to draw the overhead textured map view.
 * @param dax The x coordinate to center on the map.
 * @param day The y coordinate to center on the map.
 * @param zoome The zoom to apply to the map.
 * @param ang The angle to rotate the map by.
 */
void drawmapview(long dax, long day, long zoome, short ang);

/**@brief Sets the viewing window for 3D mode.
 *
 * This function will cause the engine to draw
 * the 3D view in a specified portion of the screen.
 * @param x1 upper left X coordinate.
 * @param y1 upper left Y coordinate.
 * @param x2 lower right X coordinate.
 * @param y2 lower right Y coordinate.
 * @remark Example: For full screen 320*200, call like this: setview(0L,0L,319L,199L);
 */
void setview(long x1, long y1, long x2, long y2);

/**@brief Shows a tile on screen, saving the previous view.
 *
 * This function will show a tile on screen, saving the previous
 * view.  You can call this multiple times, and calling \a setviewback
 * will go to the last view. If you keep calling \a setback, you
 * will eventually get back to your original screen.
 * All drawing starts in the top left corner.
 * @param tilenume Tile to show.
 * @param xsiz X size to draw.
 * @param ysiz Y size to draw.
 */
void setviewtotile(short tilenume, long xsiz, long ysiz);

/**@brief Shows the screen as it was previous to the last \a setviewtotile.
 *
 * This function will show the screen as it was before the last call to \a setviewtotile.
 */
void setviewback(void);

/**@brief Rotates a tile's image.
 *
 * This function will rotate the graphic of a tile.
 * It only works with square tiles.
 * @param tilenume The tile to perform the rotation on.
 */
void squarerotatetile(short tilenume);
void preparemirror(long dax, long day, long daz,
                   short daang, long dahoriz, short dawall,
                   short dasector, long *tposx, long *tposy,
                   short *tang);
void completemirror(void);

/**@brief Check if a clipping box intersects a wall
 *
 * This function will test if a box intersects a wall.\n
 * It returns TRUE if an intersection ocurrs.
 * @param x Center of box X.
 * @param y Center of box Y.
 * @param wallnum Wall to test against.
 * @param walldist Radius of clipping box.
 * @return TRUE if an intersection ocurred. 
 */
int clipinsidebox(long x, long y, short wallnum, long walldist);

#ifdef SUPERBUILD

/**@brief Load a voxel.
 *
 * This function will load a voxel that can be used to replace a sprite. \n
 * See notes below.
 * @param voxindex The voxel number to use.
 * @param *filename The voxel file to load.
 * @remark Ken's Notes on Using Voxels: \n
 * To actually display the voxel, you need to set the
 * (sprite[?].cstat&48) to equal 48 like this: \n
 * sprite[?].cstat |= 48; \n
 * I have no special collision code for voxels.  They are simply
 * treated as face sprites. \n \n
 * You should set the sprite[?].picnum to equal the VOXEL
 * index of the voxel that you passed to qloadkvx. If you don't
 * do this you will see nothing.  To handle this index remapping
 * it is a good idea to make some array like this: \n
 * short picnumtovox[MAXTILES]; \n
 * and save the array in some file (or in the .GRP file) \n
 * Many other fields of the sprite structure also affect voxels,
 * such as:  ang, shade, pal, xrepeat, yrepeat. \n \n
 * Note: To view voxels in the Build editor, you will need to do
 * the same qloadkvx calls in your BSTUB.C. \n
 * And now a warning:  Voxels tend to draw the fastest when
 * they are tall and thin. \n For example, a telephone pole
 * would work just great. \n They slow down very quickly as
 * you add detail. \n This is why you don't see any large
 * voxels in SW and Blood.
 */
void qloadkvx(long voxindex, char *filename);
#endif

#ifdef __cplusplus
}
#endif

#endif /* !defined _INCLUDE_ENGINE_H_ */

/* end of engine.h ... */



