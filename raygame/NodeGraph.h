#pragma once
#include <Vector2.h>
#include "DynamicArray.h"

namespace NodeGraph
{
	struct Node;

	struct Edge
	{
		Node* target;
		float cost;
	};

	struct Node
	{
		MathLibrary::Vector2 position;

		float gScore;
		float hScore;
		float fScore;
		bool walkable = true;
		unsigned int color = 0xFFFFFFFFF;

		Node* previous;

		DynamicArray<Edge> edges;
	};

	/// <summary>
	/// Finds the quickest possible path in order to reach a specific target
	/// </summary>
	/// <param name="start"> The current node the agent is on </param>
	/// <param name="end"> The end node the agent intends to reach </param>
	/// <returns> A dynamic array containing a path to the end node</returns>
	DynamicArray<Node*> findPath(Node* start, Node* end);

	/// <summary>
	/// A method for debugging purposes, draws out the node graph
	/// </summary>
	/// <param name="start"> The starting node to draw</param>
	void drawGraph(Node* start);

	/// <summary>
	/// Draws the node passed into the method
	/// </summary>
	/// <param name="node"> The node to draw </param>
	/// <param name="size"> The node size </param>
	void drawNode(Node* node, float size = 14);

	/// <summary>
	/// Draw the nodes connected to a specific node
	/// </summary>
	/// <param name="node"> The parent node to the connected node </param>
	/// <param name="drawnList"> A refrence to the list of Nodes already drawn </param>
	void drawConnectedNodes(Node* node, DynamicArray<Node*>& drawnList);

	/// <summary>
	/// Resets the nodegraph
	/// </summary>
	/// <param name="start"> The node to start resetting from </param>
	void resetGraphScore(Node* start);

	/// <summary>
	/// Reset the list of connected nodes
	/// </summary>
	/// <param name="node"> The root node </param>
	/// <param name="resetList"> The list of nodes that have already been reset </param>
	void resetConnectedNodes(Node* node, DynamicArray<Node*>& resetList);
}