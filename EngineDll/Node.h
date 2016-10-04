#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Entity3D.h"

class Mesh;

#include "Export.h"

class DllExport Node : public Entity3D{
public:
	Node();
	~Node();
	void addChild(Entity3D* pkChild);
	void removeChild(Entity3D* pkChild);
	void updateTransformation();
	void draw();

	const std::vector<Entity3D*>& childs() const;

private:
	std::vector<Entity3D*> _childs;
};
#endif