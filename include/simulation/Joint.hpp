/*
 * Joint.hpp
 *
 *  Created on: Jun 2, 2011
 *      Author: markus
 */

#ifndef JOINT_HPP_
#define JOINT_HPP_

#include <m3d/m3d.hpp>
#include <dMatrix.h>
#include <dVector.h>
#include <NewtonCustomJoint.h>
#include <CustomHinge.h>
#ifdef _WIN32
#include <boost/tr1/memory.hpp>
#else
#include <tr1/memory>
#endif
#include <list>

namespace sim {

using namespace m3d;

class __Object;
typedef std::tr1::shared_ptr<__Object> Object;
class __Joint;
typedef std::tr1::shared_ptr<__Joint> Joint;
class __Hinge;
typedef std::tr1::shared_ptr<__Hinge> Hinge;

class __Joint {
public:
	typedef enum { HINGE } Type;

	Type type;

	__Joint(Type type);

	static void save(const __Joint& joint /*node*/);
	Joint load(const std::list<Object>& list/*node*/);
};

class __Hinge : public __Joint, public CustomHinge {
protected:
	__Hinge(Vec3f pivot, Vec3f pinDir,
			const Object& child, const Object& parent,
			const dMatrix& pinAndPivot,
			const NewtonBody* childBody, const NewtonBody* parentBody);
public:
	Vec3f pivot;
	Vec3f pinDir;
	Object child;
	Object parent;

	static Hinge create(Vec3f pivot, Vec3f pinDir, const Object& child, const Object& parent);

	static void save(const __Hinge& hinge /* node */);
	static Hinge load(const std::list<Object>& list/*node*/);
};


}

#endif /* JOINT_HPP_ */
