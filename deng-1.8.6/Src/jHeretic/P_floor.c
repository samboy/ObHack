#include "jHeretic/Doomdef.h"
#include "jHeretic/P_local.h"
#include "jHeretic/Soundst.h"

//==================================================================
//==================================================================
//
//                              FLOORS
//
//==================================================================
//==================================================================

//==================================================================
//
//  Move a plane (floor or ceiling) and check for crushing
//
//==================================================================
result_e T_MovePlane(sector_t *sector, fixed_t speed, fixed_t dest,
					 boolean crush, int floorOrCeiling, int direction)
{
	boolean flag;
	fixed_t lastpos;
	fixed_t *ptarget = &sector->planes[floorOrCeiling].target;
	fixed_t *pspeed = &sector->planes[floorOrCeiling].speed;

	// Tell the engine what's going on.
	*ptarget = dest;
	*pspeed = speed;

	switch (floorOrCeiling)
	{
	case 0:					// FLOOR
		switch (direction)
		{
		case -1:				// DOWN
			if(sector->floorheight - speed < dest)
			{
				lastpos = sector->floorheight;
				sector->floorheight = dest;
				flag = P_ChangeSector(sector, crush);
				if(flag == true)
				{
					*ptarget = sector->floorheight = lastpos;
					*pspeed = 0;
					P_ChangeSector(sector, crush);
					//return crushed;
				}
				//gi.Sv_SectorReport(sector, false, sector->floorheight, 0, -1, -1);
				return pastdest;
			}
			else
			{
				lastpos = sector->floorheight;
				sector->floorheight -= speed;
				flag = P_ChangeSector(sector, crush);
				if(flag == true)
				{
					*ptarget = sector->floorheight = lastpos;
					*pspeed = 0;
					P_ChangeSector(sector, crush);
					//gi.Sv_SectorReport(sector, false, sector->floorheight, 0, -1, -1);
					return crushed;
				}
				//gi.Sv_SectorReport(sector, false, dest, speed, -1, -1);
			}
			break;

		case 1:				// UP
			if(sector->floorheight + speed > dest)
			{
				lastpos = sector->floorheight;
				sector->floorheight = dest;
				flag = P_ChangeSector(sector, crush);
				if(flag == true)
				{
					*ptarget = sector->floorheight = lastpos;
					*pspeed = 0;
					P_ChangeSector(sector, crush);
					//return crushed;
				}
				//gi.Sv_SectorReport(sector, false, sector->floorheight, 0, -1, -1);
				return pastdest;
			}
			else				// COULD GET CRUSHED
			{
				lastpos = sector->floorheight;
				sector->floorheight += speed;
				flag = P_ChangeSector(sector, crush);
				if(flag == true)
				{
					if(crush == true)
					{
						//gi.Sv_SectorReport(sector, false, dest, speed, -1, -1);
						return crushed;
					}
					*ptarget = sector->floorheight = lastpos;
					*pspeed = 0;
					P_ChangeSector(sector, crush);
					//gi.Sv_SectorReport(sector, false, sector->floorheight, 0, -1, -1);
					return crushed;
				}
				//gi.Sv_SectorReport(sector, false, dest, speed, -1, -1);
			}
			break;
		}
		break;

	case 1:					// CEILING
		switch (direction)
		{
		case -1:				// DOWN
			if(sector->ceilingheight - speed < dest)
			{
				lastpos = sector->ceilingheight;
				sector->ceilingheight = dest;
				flag = P_ChangeSector(sector, crush);
				if(flag == true)
				{
					*ptarget = sector->ceilingheight = lastpos;
					*pspeed = 0;
					P_ChangeSector(sector, crush);
					//return crushed;
				}
				//gi.Sv_SectorReport(sector, true, sector->ceilingheight, 0, -1, -1);
				return pastdest;
			}
			else				// COULD GET CRUSHED
			{
				lastpos = sector->ceilingheight;
				sector->ceilingheight -= speed;
				flag = P_ChangeSector(sector, crush);
				if(flag == true)
				{
					if(crush == true)
					{
						//gi.Sv_SectorReport(sector, true, dest, speed, -1, -1);
						return crushed;
					}
					*ptarget = sector->ceilingheight = lastpos;
					*pspeed = 0;
					P_ChangeSector(sector, crush);
					//gi.Sv_SectorReport(sector, true, sector->ceilingheight, 0, -1, -1);
					return crushed;
				}
				//gi.Sv_SectorReport(sector, true, dest, speed, -1, -1);
			}
			break;

		case 1:				// UP
			if(sector->ceilingheight + speed > dest)
			{
				lastpos = sector->ceilingheight;
				sector->ceilingheight = dest;
				flag = P_ChangeSector(sector, crush);
				if(flag == true)
				{
					*ptarget = sector->ceilingheight = lastpos;
					*pspeed = 0;
					P_ChangeSector(sector, crush);
					//return crushed;
				}
				//gi.Sv_SectorReport(sector, true, sector->ceilingheight, 0, -1, -1);
				return pastdest;
			}
			else
			{
				lastpos = sector->ceilingheight;
				sector->ceilingheight += speed;
				flag = P_ChangeSector(sector, crush);
				//gi.Sv_SectorReport(sector, true, dest, speed, -1, -1);
#if 0							//-------- UNUSED --------
				if(flag == true)
				{
					sector->ceilingheight = lastpos;
					P_ChangeSector(sector, crush);
					return crushed;
				}
#endif							//-------- UNUSED --------
			}
			break;
		}
		break;

	}
	return ok;
}

//==================================================================
//
//  MOVE A FLOOR TO IT'S DESTINATION (UP OR DOWN)
//
//==================================================================
void T_MoveFloor(floormove_t * floor)
{
	result_e res;

	res =
		T_MovePlane(floor->sector, floor->speed, floor->floordestheight,
					floor->crush, 0, floor->direction);
	if(!(leveltime & 7))
	{
		//S_StartSound((mobj_t *)&floor->sector->soundorg, sfx_dormov);
		S_SectorSound(floor->sector, sfx_dormov);
	}

	if(res == pastdest)
	{
		floor->sector->planes[PLN_FLOOR].speed = 0;
		floor->sector->specialdata = NULL;
		if(floor->type == raiseBuildStep)
		{
			S_SectorSound(floor->sector, sfx_pstop);
		}
		if(floor->direction == 1)
			switch (floor->type)
			{
			case donutRaise:
				floor->sector->special = floor->newspecial;
				floor->sector->floorpic = floor->texture;
				/*gi.Sv_SectorReport(floor->sector, false, 
				   floor->sector->floorheight, 0, floor->texture, -1); */
			default:
				break;
			}
		else if(floor->direction == -1)
			switch (floor->type)
			{
			case lowerAndChange:
				floor->sector->special = floor->newspecial;
				floor->sector->floorpic = floor->texture;
				/*gi.Sv_SectorReport(floor->sector, false, 
				   floor->sector->floorheight, 0, floor->texture, -1); */
			default:
				break;
			}
		P_RemoveThinker(&floor->thinker);
	}

}

//==================================================================
//
//  HANDLE FLOOR TYPES
//
//==================================================================
int EV_DoFloor(line_t *line, floor_e floortype)
{
	int     secnum;
	int     rtn;
	int     i;
	sector_t *sec;
	floormove_t *floor;

	secnum = -1;
	rtn = 0;
	while((secnum = P_FindSectorFromLineTag(line, secnum)) >= 0)
	{
		sec = &sectors[secnum];

		//  ALREADY MOVING?  IF SO, KEEP GOING...
		if(sec->specialdata)
			continue;

		//
		//  new floor thinker
		//
		rtn = 1;
		floor = Z_Malloc(sizeof(*floor), PU_LEVSPEC, 0);
		P_AddThinker(&floor->thinker);
		sec->specialdata = floor;
		floor->thinker.function = T_MoveFloor;
		floor->type = floortype;
		floor->crush = false;
		switch (floortype)
		{
		case lowerFloor:
			floor->direction = -1;
			floor->sector = sec;
			floor->speed = FLOORSPEED;
			floor->floordestheight = P_FindHighestFloorSurrounding(sec);
			break;
		case lowerFloorToLowest:
			floor->direction = -1;
			floor->sector = sec;
			floor->speed = FLOORSPEED;
			floor->floordestheight = P_FindLowestFloorSurrounding(sec);
			break;
		case turboLower:
			floor->direction = -1;
			floor->sector = sec;
			floor->speed = FLOORSPEED * 4;
			floor->floordestheight =
				(8 * FRACUNIT) + P_FindHighestFloorSurrounding(sec);
			break;
		case raiseFloorCrush:
			floor->crush = true;
		case raiseFloor:
			floor->direction = 1;
			floor->sector = sec;
			floor->speed = FLOORSPEED;
			floor->floordestheight = P_FindLowestCeilingSurrounding(sec);
			if(floor->floordestheight > sec->ceilingheight)
				floor->floordestheight = sec->ceilingheight;
			floor->floordestheight -=
				(8 * FRACUNIT) * (floortype == raiseFloorCrush);
			break;
		case raiseFloorToNearest:
			floor->direction = 1;
			floor->sector = sec;
			floor->speed = FLOORSPEED;
			floor->floordestheight =
				P_FindNextHighestFloor(sec, sec->floorheight);
			break;
		case raiseFloor24:
			floor->direction = 1;
			floor->sector = sec;
			floor->speed = FLOORSPEED;
			floor->floordestheight =
				floor->sector->floorheight + 24 * FRACUNIT;
			break;
		case raiseFloor24AndChange:
			floor->direction = 1;
			floor->sector = sec;
			floor->speed = FLOORSPEED;
			floor->floordestheight =
				floor->sector->floorheight + 24 * FRACUNIT;
			sec->floorpic = line->frontsector->floorpic;
			sec->special = line->frontsector->special;
			break;
		case raiseToTexture:
			{
				int     minsize = MAXINT;
				side_t *side;

				floor->direction = 1;
				floor->sector = sec;
				floor->speed = FLOORSPEED;
				for(i = 0; i < sec->linecount; i++)
					if(twoSided(secnum, i))
					{
						side = getSide(secnum, i, 0);
						if(side->bottomtexture >= 0)
						{
							Set(DD_TEXTURE_HEIGHT_QUERY, side->bottomtexture);
							if(Get(DD_QUERY_RESULT) < minsize)
								minsize = Get(DD_QUERY_RESULT);
						}
						side = getSide(secnum, i, 1);
						if(side->bottomtexture >= 0)
						{
							Set(DD_TEXTURE_HEIGHT_QUERY, side->bottomtexture);
							if(Get(DD_QUERY_RESULT) < minsize)
								minsize = Get(DD_QUERY_RESULT);
						}
					}
				floor->floordestheight = floor->sector->floorheight + minsize;
			}
			break;
		case lowerAndChange:
			floor->direction = -1;
			floor->sector = sec;
			floor->speed = FLOORSPEED;
			floor->floordestheight = P_FindLowestFloorSurrounding(sec);
			floor->texture = sec->floorpic;
			for(i = 0; i < sec->linecount; i++)
				if(twoSided(secnum, i))
				{
					if(getSide(secnum, i, 0)->sector - sectors == secnum)
					{
						sec = getSector(secnum, i, 1);
						floor->texture = sec->floorpic;
						floor->newspecial = sec->special;
						break;
					}
					else
					{
						sec = getSector(secnum, i, 0);
						floor->texture = sec->floorpic;
						floor->newspecial = sec->special;
						break;
					}
				}
		default:
			break;
		}
	}
	return rtn;
}

//==================================================================
//
//  BUILD A STAIRCASE!
//
//==================================================================
int EV_BuildStairs(line_t *line, fixed_t stepDelta)
{
	int     secnum;
	int     height;
	int     i;
	int     newsecnum;
	int     texture;
	int     ok;
	int     rtn;
	sector_t *sec, *tsec;
	floormove_t *floor;

	secnum = -1;
	rtn = 0;
	while((secnum = P_FindSectorFromLineTag(line, secnum)) >= 0)
	{
		sec = &sectors[secnum];

		// ALREADY MOVING?  IF SO, KEEP GOING...
		if(sec->specialdata)
			continue;

		//
		// new floor thinker
		//
		rtn = 1;
		height = sec->floorheight + stepDelta;
		floor = Z_Malloc(sizeof(*floor), PU_LEVSPEC, 0);
		P_AddThinker(&floor->thinker);
		sec->specialdata = floor;
		floor->thinker.function = T_MoveFloor;
		floor->type = raiseBuildStep;
		floor->direction = 1;
		floor->sector = sec;
		floor->speed = FLOORSPEED;
		floor->floordestheight = height;

		texture = sec->floorpic;

		//
		// Find next sector to raise
		// 1.   Find 2-sided line with same sector side[0]
		// 2.   Other side is the next sector to raise
		//
		do
		{
			ok = 0;
			for(i = 0; i < sec->linecount; i++)
			{
				if(!((sec->Lines[i])->flags & ML_TWOSIDED))
					continue;

				tsec = (sec->Lines[i])->frontsector;
				newsecnum = tsec - sectors;
				if(secnum != newsecnum)
					continue;
				tsec = (sec->Lines[i])->backsector;
				newsecnum = tsec - sectors;
				if(tsec->floorpic != texture)
					continue;

				height += stepDelta;
				if(tsec->specialdata)
					continue;

				sec = tsec;
				secnum = newsecnum;
				floor = Z_Malloc(sizeof(*floor), PU_LEVSPEC, 0);
				P_AddThinker(&floor->thinker);
				sec->specialdata = floor;
				floor->thinker.function = T_MoveFloor;
				floor->type = raiseBuildStep;
				floor->direction = 1;
				floor->sector = sec;
				floor->speed = FLOORSPEED;
				floor->floordestheight = height;
				ok = 1;
				break;
			}
		} while(ok);
	}
	return (rtn);
}