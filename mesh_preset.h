#ifndef MESH_PRESET_H
#define MESH_PRESET_H

#include "preset.h"


class MeshPreset : public Preset
{
	GDCLASS(MeshPreset, Preset);
protected:
	static void _bind_methods();
private:
	Ref<Mesh> mesh;
	TypedArray<int> materials;
public:
	MeshPreset();
	~MeshPreset();

	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void set_materials(const TypedArray<int>& value);
	TypedArray<int> get_materials() const;


	void build_mesh(const Array& arrays, const int surface_index, const Vector3& position, const Vector3& rotation);

	static Ref<MeshPreset> instantiate(const String& uuid, const String& name, const Ref<Mesh>& mesh, Array materials);
	static Vector3 rotate_vertex(const Vector3& vertex, const Vector3i& rotation);
	static Vector3 get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c);
};

#endif // !MESH_PRESET_H