#include "Pitch.h"

#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Pitch::Pitch(const QString name /* = "Pitch" */)
	: dt::Node(name) {}

void Pitch::onUpdate(double time_diff) 
{
	Node::onUpdate(time_diff);
	//dt::Logger::get().error("shi***************t\n");
}

void Pitch::onInitialize() 
{
	// Realize a mesh 
	OgreProcedural::PlaneGenerator().setSizeX(13.6f).setSizeY(21.0f).setUTile(1.0).setVTile(1.0).realizeMesh("Plane");
	auto plane_node = this->addChildNode(new dt::Node("planenode"));
	plane_node->addComponent(new dt::MeshComponent("Plane", "PrimitivesTest/Pebbles", "plane-mesh"));
	plane_node->addComponent(new dt::PhysicsBodyComponent("plane-mesh", "plane-body",
		dt::PhysicsBodyComponent::CONVEX, 0.0f));

	// Initialize the ball
	mBall = new Ball("Ball.mesh");
	mBall->setPosition(0, 10, 0);
	addChildNode(mBall);	
}

void Pitch::onDeinitialize() 
{

}



