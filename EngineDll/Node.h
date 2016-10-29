#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Entity3D.h"
#include "Importer.h"

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
	Entity3D& findChild(std::string name);

	const std::vector<Entity3D*>& childs() const;

private:
	std::string _name;
	std::vector<Entity3D*> _childs;
};
#endif