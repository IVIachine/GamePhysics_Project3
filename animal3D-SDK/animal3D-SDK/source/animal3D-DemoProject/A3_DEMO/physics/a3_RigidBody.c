/*
	Copyright 2011-2018 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_RigidBody.c/.cpp
	Implementation of rigid body.
*/

#include "a3_RigidBody.h"


//-----------------------------------------------------------------------------

// internal helpers

// internal helper to multiply vec3 with quaternion (not rotation!)
// results in a quaternion, useful for derivative calculation
inline a3real4r a3rigidbodyMultiplyVec3Quat(a3real4p q_out, const a3real3p vL, const a3real4p qR)
{
	// ****TO-DO: 
	//	- implement simplified quaternion multiplication


	// done
	return q_out;
}

// internal helper to perform vec3 transform
inline a3real3r a3rigidbodyTransformPoint3_internal(a3real3p v_out, const a3real3p v, const a3real4x4p t)
{
	// ****TO-DO: 
	//	- transform vector by matrix


	// done
	return v_out;
}

// internal helper to perform rebase
inline a3real3x3r a3rigidbodyRebaseMatrix_internal(a3real3x3p m_out, const a3real3x3p m, const a3real4x4p t)
{
	// ****TO-DO: 
	//	- utility to rebase matrix given a transform: 
	//		final = t * m * t^-1
	//	- if we know t represents a rotation then its inverse is its transpose
	//	- possibly messy but that means direct and therefore efficient


	// done
	return m_out;
}


//-----------------------------------------------------------------------------

// named Euler methods

// explicit Euler: integrate current velocity
extern inline void a3rigidbodyIntegrateEulerExplicit(a3_RigidBody *rb, const a3real dt)
{
	a3vec3 d;

	//	x(t+dt) = x(t) + f(t)dt
	//					 f(t) = dx/dt = v(t)
	//	x(t+dt) = x(t) + v(t)dt
	a3real3Add(rb->position.v, a3real3ProductS(d.v, rb->velocity.v, dt));

	//	v(t+dt) = v(t) + g(t)dt
	//					 g(t) = dv/dt = a(t)
	//	v(t+dt) = v(t) + a(t)dt
	a3real3Add(rb->velocity.v, a3real3ProductS(d.v, rb->acceleration.v, dt));


	// ****TO-DO: 
	//	- integrate rotation using explicit Euler formula
	//	- integrate angular velocity
}

// semi-implicit Euler: integrate next velocity
extern inline void a3rigidbodyIntegrateEulerSemiImplicit(a3_RigidBody *rb, const a3real dt)
{
	a3vec3 d;

	//	v(t+dt) = v(t) + a(t)dt
	a3real3Add(rb->velocity.v, a3real3ProductS(d.v, rb->acceleration.v, dt));

	//	x(t+dt) = x(t) + v(t+dt)dt
	a3real3Add(rb->position.v, a3real3ProductS(d.v, rb->velocity.v, dt));


	// ****TO-DO: 
	//	- integrate rotation using semi-implicit euler formula
	//	- integrate angular velocity
}

// kinematic: integrate average of current and next velocities
extern inline void a3rigidbodyIntegrateEulerKinematic(a3_RigidBody *rb, const a3real dt)
{
	a3vec3 d;

	//	x(t+dt) = x(t) + v(t)dt + a(t)dt2 / 2
	a3real3Add(rb->position.v, a3real3ProductS(d.v, a3real3Sum(d.v, rb->velocity.v, a3real3ProductS(d.v, rb->acceleration.v, a3realHalf * dt)), dt));

	//	v(t+dt) = v(t) + a(t)dt
	a3real3Add(rb->velocity.v, a3real3ProductS(d.v, rb->acceleration.v, dt));


	// ****TO-DO: 
	//	- integrate rotation using kinematic formula
	//	- integrate angular velocity
}


//-----------------------------------------------------------------------------

// rigid body helpers

// set mass
extern inline int a3rigidbodySetMass(a3_RigidBody *rb, const a3real mass)
{
	if (rb)
	{
		// correctly set mass: 
		//	- valid or contingency for invalid
		if (mass > a3realZero)
		{
			rb->mass = mass;
			rb->massInv = a3recip(mass);
			return 1;
		}
		else
		{
			// invalid mass shall describe "static" particle
			rb->mass = rb->massInv = a3realZero;
			return 0;
		}
	}
	return -1;
}

// calculate inertia tensor for shapes
//	(set mass first!)
//	solid sphere
extern inline int a3rigidbodySetLocalInertiaTensorSphereSolid(a3_RigidBody *rb, const a3real radius)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}
//	hollow sphere
extern inline int a3rigidbodySetLocalInertiaTensorSphereHollow(a3_RigidBody *rb, const a3real radius)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}
//	solid box
extern inline int a3rigidbodySetLocalInertiaTensorBoxSolid(a3_RigidBody *rb, const a3real width, const a3real height, const a3real depth)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}
//	hollow box
extern inline int a3rigidbodySetLocalInertiaTensorBoxHollow(a3_RigidBody *rb, const a3real width, const a3real height, const a3real depth)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}
//	solid cylinder
extern inline int a3rigidbodySetLocalInertiaTensorCylinderSolid(a3_RigidBody *rb, const a3real radius, const a3real height, const int bodyAxis)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}
//	solid cone about apex
extern inline int a3rigidbodySetLocalInertiaTensorConeSolidApex(a3_RigidBody *rb, const a3real radius, const a3real height, const int bodyAxis)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}
//	rod about end
extern inline int a3rigidbodySetLocalInertiaTensorRodEnd(a3_RigidBody *rb, const a3real length, const int bodyAxis)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}
//	rod about center
extern inline int a3rigidbodySetLocalInertiaTensorRodCenter(a3_RigidBody *rb, const a3real length, const int bodyAxis)
{
	if (rb)
	{
	//	a3mat3 I = a3identityMat3;

		// ****TO-DO: 

		return 1;
	}
	return 0;
}

// calculate total mass and center of mass from a set of influences
extern inline int a3rigidbodyCalculateLocalCenterOfMass(a3_RigidBody *rb, const a3real3 *influenceList, const a3real *massList, const unsigned int count)
{
	if (rb && influenceList && massList)
	{
	//	unsigned int i;
	//	a3vec3 c, dc;
	//	a3real m, dm;

		// ****TO-DO: 
		//	- accumulate mass and weighted total of influences
		//	- store mass and multiply weighted total by inv mass

		return 1;
	}
	return 0;
}

// calculate inertia tensor and inverse from a set of influences
//	(calculate center of mass first!)
extern inline int a3rigidbodyCalculateLocalInertiaTensor(a3_RigidBody *rb, const a3real3 *influenceList, const a3real *massList, const unsigned int count)
{
	if (rb && influenceList && massList)
	{
	//	unsigned int i;
	//	a3mat3 I = a3identityMat3;
	//	a3vec3 r;
	//	a3real m;

		// ****TO-DO: 
		//	- accumulate unique components of tensor
		//	- copy symmetric elements, store and invert

		return 1;
	}
	return 0;
}


// check if particle is moving
extern inline int a3rigidbodyIsMoving(const a3_RigidBody *rb)
{
	if (rb)
	{
		// determine if particle is moving (speed is not zero)
		const a3real v = a3real3LengthSquared(rb->velocity.v);
		return a3isNotNearZero(v);	// safe
	//	return (v != a3realZero);	// unsafe
	}
	return -1;
}

// check if particle is rotating
extern inline int a3rigidbodyIsRotating(const a3_RigidBody *rb)
{
	if (rb)
	{
		// ****TO-DO: 
		// determine if particle is rotating (angular speed is not zero)

	}
	return -1;
}


// apply force at center of mass
extern inline int a3rigidbodyApplyForceDirect(a3_RigidBody *rb, const a3real3p f)
{
	if (rb && f)
	{
		// F(t) += F_applied
		a3real3Add(rb->force.v, f);
		return 1;
	}
	return 0;
}

// apply force at other location
extern inline int a3rigidbodyApplyForceLocation(a3_RigidBody *rb, const a3real3p f, const a3real3p loc)
{
	if (rb && f && loc)
	{
		// ****TO-DO: 
		//	arm = loc - c_mass
		//	torque += arm x F_applied

		return 1;
	}
	return 0;
}

// convert force to acceleration
extern inline int a3rigidbodyConvertForce(a3_RigidBody *rb)
{
	if (rb)
	{
		// a(t) = F(t) / m
		a3real3ProductS(rb->acceleration.v, rb->force.v, rb->massInv);
		return 1;
	}
	return 0;
}

// convert torque to angular acceleration
extern inline int a3rigidbodyConvertTorque(a3_RigidBody *rb)
{
	if (rb)
	{
		// ****TO-DO: 
		// alpha(t) = I_inv(t) * torque(t)

		return 1;
	}
	return 0;
}

// reset force
extern inline int a3rigidbodyResetForce(a3_RigidBody *rb)
{
	if (rb)
	{
		a3real3Set(rb->force.v, a3realZero, a3realZero, a3realZero);
		return 1;
	}
	return -1;
}

// reset torque
extern inline int a3rigidbodyResetTorque(a3_RigidBody *rb)
{
	if (rb)
	{
		// ****TO-DO: 

		return 1;
	}
	return -1;
}


// update center of mass relative to world
extern inline int a3rigidbodyUpdateCenterOfMass(a3_RigidBody *rb, const a3real4x4p transform)
{
	if (rb && transform)
	{
		// ****TO-DO: 
		// multiply matrix by local center of mass
		
		return 1;
	}
	return 0;
}

// update inertia tensor
extern inline int a3rigidbodyUpdateInertiaTensor(a3_RigidBody *rb, const a3real4x4p transform)
{
	if (rb && transform)
	{
		// ****TO-DO: 
		// change of basis: 
		//	- current tensor is R*I*R^-1
		//	- current tensor inverse is R*I^-1*R^-1
		
		return 1;
	}
	return 0;
}


//-----------------------------------------------------------------------------
