#include "voxel_container_data.h"

void VoxelContainerData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_container_size", "value"), &VoxelContainerData::set_container_size);
	ClassDB::bind_method(D_METHOD("get_container_size"), &VoxelContainerData::get_container_size);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &VoxelContainerData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelContainerData::get_voxels);

	ClassDB::bind_method(D_METHOD("set_voxel", "value"), &VoxelContainerData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel"), &VoxelContainerData::get_voxel);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "container_size"), "set_container_size", "get_container_size");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "voxels"), "set_voxels", "get_voxels");

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(BASICS);
	BIND_ENUM_CONSTANT(MESH);
	BIND_ENUM_CONSTANT(DEVICE);
}

VoxelContainerData::VoxelContainerData()
{
	set_container_size(Vector3i(8, 8, 8));
}

VoxelContainerData::~VoxelContainerData()
{
}


void VoxelContainerData::set_container_size(const Vector3i& value) {
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "The container size is an invalid value");
	container_size = value;

	voxels.resize(container_size.x * container_size.y * container_size.z);
}

Vector3i VoxelContainerData::get_container_size() const {
	return container_size;
}

void VoxelContainerData::set_voxels(const PackedByteArray& value)
{
	voxels = value.decompress(4096).to_int32_array();
}

PackedByteArray VoxelContainerData::get_voxels() const
{
	return voxels.to_byte_array().compress();
}

void VoxelContainerData::set_voxel(const Vector3i& position, const Voxel& value)
{
	if (position.x < 0 || position.x >= container_size.x ||
		position.y < 0 || position.y >= container_size.y ||
		position.z < 0 || position.z >= container_size.z) {
		return;
	}
	int index = ((position.x * container_size.y * container_size.z) + (position.y * container_size.z) + position.z);
	voxels[index] = value;
}

Voxel VoxelContainerData::get_voxel(const Vector3i& position) const
{
	if (position.x < 0 || position.x >= container_size.x ||
		position.y < 0 || position.y >= container_size.y ||
		position.z < 0 || position.z >= container_size.z) {
		return EMPTY_VOXEL;
	}
	int index = ((position.x * container_size.y * container_size.z) + (position.y * container_size.z) + position.z);
	return voxels[index];
}

//int VoxelContainerData::register_preset(const Ref<Preset>& value)
//{
//	String uuid = value->get_uuid();
//	int index = -1;
//	if (preset_map.get(uuid, nullptr).get_type() != Variant::NIL) {
//		UtilityFunctions::printerr("This preset + " + value->get_name() + " + is already registered");
//		return index;
//	}
//	String name = value->get_class();
//	Array presets;
//	if (name == StringName("CustomMaterial")) {
//		presets = custom_materials;
//	}
//	else if (name == StringName("BasicsPreset")) {
//		presets = basics_presets;
//	}
//	else if (name == StringName("DevicePreset")) {
//		presets = device_presets;
//	}
//	else {
//		UtilityFunctions::printerr("This object + " + value->get_class() + " + is not a preset");
//		return index;
//	}
//	for (index = 0; index < presets.size(); index++)
//	{
//		if (presets[index].get_type() == Variant::NIL) {
//			preset_map[uuid] = index;
//			presets[index] = value;
//			return index;
//		}
//	}
//	index = presets.size();
//	presets.push_back(value);
//	preset_map[uuid] = index;
//	return index;
//}