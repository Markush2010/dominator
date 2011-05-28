/*
 * Simulation.hpp
 *
 *  Created on: May 27, 2011
 *      Author: Markus Doellinger
 */

#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#include <util/InputAdapters.hpp>
#include <util/Clock.hpp>
#include <opengl/Camera.hpp>
#include <simulation/Object.hpp>
#include <map>
#include <Newton.h>


namespace sim {

using namespace m3d;

typedef std::map<int, Object> ObjectMap;

class Simulation : public util::MouseListener {
private:
	static Simulation* s_instance;
	Simulation(util::KeyAdapter& keyAdapter,
				util::MouseAdapter& mouseAdapter);
	virtual ~Simulation();

protected:
	util::KeyAdapter& m_keyAdapter;
	util::MouseAdapter& m_mouseAdapter;
	util::Clock m_clock;

	ogl::Camera m_camera;

	ObjectMap m_objects;

	NewtonWorld* m_world;
	float m_gravity;

public:
	/**
	 * Creates a new instance of the Simulation.
	 *
	 * @param keyAdapter
	 * @param mouseAdapter
	 */
	static void createInstance(util::KeyAdapter& keyAdapter,
								util::MouseAdapter& mouseAdapter);

	/**
	 *
	 */
	static void destroyInstance();

	/**
	 * Returns the singleton instance of the Simulation.
	 *
	 * @return The Simulation.
	 */
	static Simulation& instance();

	/** @return The handle to the NewtonWorld */
	NewtonWorld* getWorld() const;

	/** @return Returns the current gravity */
	float getGravity() const;

	virtual void mouseMove(int x, int y);
	virtual void mouseButton(util::Button button, bool down, int x, int y);


	void update();
	void render();
};


inline NewtonWorld* Simulation::getWorld() const
{
	return m_world;
}

inline float Simulation::getGravity() const
{
	return m_gravity;
}

}

#endif /* SIMULATION_HPP_ */
