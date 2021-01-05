#ifndef OBJMGR_H
#define OBJMGR_H

#include "Obj4D.h"

class ObjMgr
{
	public:
		ObjMgr();
		~ObjMgr();
		void addObj(Object4D * _object);
		void process();
	private:
		std::vector<Object4D *> objects;
};

#endif