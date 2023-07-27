#pragma once

/*
	------------------------------------------------------------------------------
		Licensing information can be found at the end of the file.
	------------------------------------------------------------------------------

	cute_tiled.h - v1.06

	To create implementation (the function definitions)
		#define CUTE_TILED_IMPLEMENTATION
	in *one* C/CPP file (translation unit) that includes this file

	SUMMARY

		Parses Tiled (http://www.mapeditor.org/) files saved as the JSON file
		format. See http://doc.mapeditor.org/en/latest/reference/json-map-format/
		for a complete description of the JSON Tiled format. An entire map file
		is loaded up in entirety and used to fill in a set of structs. The entire
		struct collection is then handed to the user.

		This header is up to date with Tiled's documentation Revision 40049fd5 and
		verified to work with Tiled stable version 1.4.1.
		http://doc.mapeditor.org/en/latest/reference/json-map-format/

		Here is a past discussion thread on this header:
		https://www.reddit.com/r/gamedev/comments/87680n/cute_tiled_tiled_json_map_parserloader_in_c/

	Revision history:
		1.00 (03/24/2018) initial release
		1.01 (05/04/2018) tile descriptors in tilesets for collision geometry
		1.02 (05/07/2018) reverse lists for ease of use, incorporate fixes by ZenToad
		1.03 (01/11/2019) support for Tiled 1.2.1 with the help of dpeter99 and tanis2000
		1.04 (04/30/2020) support for Tiled 1.3.3 with the help of aganm
		1.05 (07/19/2020) support for Tiled 1.4.1 and tileset tile animations
		1.06 (04/05/2021) support for Tiled 1.5.0 parallax
		1.07 (03/01/2022) support for c89
*/

/*
	Contributors:
		ZenToad           1.02 - Bug reports and goto statement errors for g++
		dpeter99          1.03 - Help with updating to Tiled 1.2.1 JSON format
		tanis2000         1.03 - Help with updating to Tiled 1.2.1 JSON format
		aganm             1.04 - Help with updating to Tiled 1.3.3 JSON format
		mupf              1.07 - Adding support for C89
*/

/*
	DOCUMENTATION

		Load up a Tiled json exported file, either from disk or memory, like so:

			cute_tiled_map_t* map = cute_tiled_load_map_from_memory(memory, size, 0);

		Then simply access the map's fields like so:

			// get map width and height
			int w = map->width;
			int h = map->height;

			// loop over the map's layers
			cute_tiled_layer_t* layer = map->layers;
			while (layer)
			{
				int* data = layer->data;
				int data_count = layer->data_count;

				// do something with the tile data
				UserFunction_HandleTiles(data, data_count);

				layer = layer->next;
			}

		Finally, free it like so:

			cute_tiled_free_map(map);

	LIMITATIONS

		More uncommon fields are not supported, and are annotated in this header.
		Search for "Not currently supported." without quotes to find them. cute_tiled
		logs a warning whenever a known unsupported field is encountered, and will
		attempt to gracefully skip the field. If a field with completely unknown
		syntax is encountered (which can happen if cute_tiled is used on a newer
		and unsupported version of Tiled), undefined behavior may occur (crashes).

		If you would like a certain feature to be supported simply open an issue on
		GitHub and provide a JSON exported map with the unsupported features. Changing
		the parser to support new fields and objects is quite easy, as long as a map
		file is provided for debugging and testing!

		GitHub : https://github.com/RandyGaul/cute_headers/

		Compression of the tile GIDs is *not* supported in this header. Exporting
		a map from Tiled will create a JSON file. This JSON file itself can very
		trivially be compressed in its entirety, thus making Tiled's internal
		compression exporting not a useful feature for this header to support.
		Simply wrap calls to `cute_tiled_load_map_from_file` in a decompression
		routine. Here is an example (assuming `zlib_uncompress` is already imp-
		lemented somewhere in the user's codebase):

			int size;
			void* uncompressed_data = zlib_uncompress(path_to_zipped_map_file, &size);
			cute_tiled_map_t* map = cute_tiled_load_map_from_memory(uncompressed_data, size, 0);
*/

// #if !defined(CUTE_TILED_H)

// Read this in the event of errors
extern const char* cute_tiled_error_reason;
extern int cute_tiled_error_line;


typedef struct cute_tiled_map_t cute_tiled_map_t;
typedef struct cute_tiled_tileset_t cute_tiled_tileset_t;

/*!
 * Load a map from disk, placed into heap allocated memory. \p mem_ctx can be
 * NULL. It is used for custom allocations.
 */
cute_tiled_map_t* cute_tiled_load_map_from_file(const char* path, void* mem_ctx);

/*!
 * Load a map from memory. \p mem_ctx can be NULL. It is used for custom allocations.
 */
cute_tiled_map_t* cute_tiled_load_map_from_memory(const void* memory, int size_in_bytes, void* mem_ctx);

/*!
 * Reverses the layers order, so they appear in reverse-order from what is shown in the Tiled editor.
 */
void cute_tiled_reverse_layers(cute_tiled_map_t* map);

/*!
 * Free all dynamic memory associated with this map.
 */
void cute_tiled_free_map(cute_tiled_map_t* map);

/*!
 * Load an external tileset from disk, placed into heap allocated memory. \p mem_ctx can be
 * NULL. It is used for custom allocations.
 *
 * Please note this function is *entirely optional*, and only useful if you want to intentionally
 * load tilesets externally from your map. If so, please also consider defining
 * `CUTE_TILED_NO_EXTERNAL_TILESET_WARNING` to disable warnings about missing embedded tilesets.
 */
cute_tiled_tileset_t* cute_tiled_load_external_tileset(const char* path, void* mem_ctx);

/*!
 * Load an external tileset from memory. \p mem_ctx can be NULL. It is used for custom allocations.
 *
 * Please note this function is *entirely optional*, and only useful if you want to intentionally
 * load tilesets externally from your map. If so, please also consider defining
 * `CUTE_TILED_NO_EXTERNAL_TILESET_WARNING` to disable warnings about missing embedded tilesets.
 */
cute_tiled_tileset_t* cute_tiled_load_external_tileset_from_memory(const void* memory, int size_in_bytes, void* mem_ctx);

/*!
 * Free all dynamic memory associated with this external tileset.
 */
void cute_tiled_free_external_tileset(cute_tiled_tileset_t* tileset);

#if !defined(CUTE_TILED_U64)
	#define CUTE_TILED_U64 unsigned long long
#endif

#if !defined(CUTE_TILED_INLINE)
	#if defined(_MSC_VER)
		#define CUTE_TILED_INLINE __inline
	#else
		#define CUTE_TILED_INLINE __inline__
	#endif
#endif

typedef struct cute_tiled_layer_t cute_tiled_layer_t;
typedef struct cute_tiled_object_t cute_tiled_object_t;
typedef struct cute_tiled_frame_t cute_tiled_frame_t;
typedef struct cute_tiled_tile_descriptor_t cute_tiled_tile_descriptor_t;
typedef struct cute_tiled_property_t cute_tiled_property_t;
typedef union cute_tiled_string_t cute_tiled_string_t;

/*!
 * To access a string, simply do: object->name.ptr; this union is needed
 * as a workaround for 32-bit builds where the size of a pointer is only
 * 32 bits.
 *
 * More info:
 * This unions is needed to support a single-pass parser, with string
 * interning, where the parser copies value directly into the user-facing
 * structures. As opposed to the parser copying values into an intermediate
 * structure, and finally copying the intermediate values into the
 * user-facing struct at the end. The latter option requires more code!
 */
union cute_tiled_string_t
{
	const char* ptr;
	CUTE_TILED_U64 hash_id;
};

typedef enum CUTE_TILED_PROPERTY_TYPE
{
	CUTE_TILED_PROPERTY_NONE,
	CUTE_TILED_PROPERTY_INT,
	CUTE_TILED_PROPERTY_BOOL,
	CUTE_TILED_PROPERTY_FLOAT,
	CUTE_TILED_PROPERTY_STRING,

	// Note: currently unused! File properties are reported as strings in
	// this header, and it is up to users to know a-priori which strings
	// contain file paths.
	CUTE_TILED_PROPERTY_FILE,

	CUTE_TILED_PROPERTY_COLOR,
} CUTE_TILED_PROPERTY_TYPE;

struct cute_tiled_property_t
{
	union
	{
		int integer;
		int boolean;
		float floating;
		cute_tiled_string_t string;
		cute_tiled_string_t file;
		int color;
	} data;
	CUTE_TILED_PROPERTY_TYPE type;
	cute_tiled_string_t name;
};

struct cute_tiled_object_t
{
	int ellipse;                         // 0 or 1. Used to mark an object as an ellipse.
	int gid;                             // GID, only if object comes from a Tilemap.
	float height;                        // Height in pixels. Ignored if using a gid.
	int id;                              // Incremental id - unique across all objects.
	cute_tiled_string_t name;            // String assigned to name field in editor.
	int point;                           // 0 or 1. Used to mark an object as a point.

	// Example to index each vert of a polygon/polyline:
	/*
		float x, y;
		for(int i = 0; i < vert_count * 2; i += 2)
		{
			x = vertices[i];
			y = vertices[i + 1];
		}
	*/
	int vert_count;
	float* vertices;                     // Represents both type `polyline` and `polygon`.
	int vert_type;                       // 1 for `polygon` and 0 for `polyline`.

	int property_count;                  // Number of elements in the `properties` array.
	cute_tiled_property_t* properties;   // Array of properties.
	float rotation;                      // Angle in degrees clockwise.
	/* template */                       // Not currently supported.
	/* text */                           // Not currently supported.
	cute_tiled_string_t type;            // String assigned to type field in editor.
	/* class */                          // Not currently supported.
	int visible;                         // 0 or 1. Whether object is shown in editor.
	float width;                         // Width in pixels. Ignored if using a gid.
	float x;                             // x coordinate in pixels.
	float y;                             // y coordinate in pixels.
	cute_tiled_object_t* next;           // Pointer to next object. NULL if final object.
};

/*!
 * Example of using both helper functions below to process the `data` pointer of a layer,
 * containing an array of `GID`s.
 *
 * for (int i = 0; i < layer->data_count; i++)
 * {
 *     int hflip, vflip, dflip;
 *     int tile_id = layer->data[i];
 *     cute_tiled_get_flags(tile_id, &hflip, &vflip, &dflip);
 *     tile_id = cute_tiled_unset_flags(tile_id);
 *     DoSomethingWithFlags(tile_id, flip, vflip, dlfip);
 *     DoSomethingWithTileID(tile_id);
 * }
 */

#define CUTE_TILED_FLIPPED_HORIZONTALLY_FLAG 0x80000000
#define CUTE_TILED_FLIPPED_VERTICALLY_FLAG   0x40000000
#define CUTE_TILED_FLIPPED_DIAGONALLY_FLAG   0x20000000


struct cute_tiled_layer_t
{
	/* chunks */                         // Not currently supported.
	/* compression; */                   // Not currently supported.
	int data_count;                      // Number of integers in `data`.
	int* data;                           // Array of GIDs. `tilelayer` only. Only support CSV style exports.
	cute_tiled_string_t draworder;       // `topdown` (default) or `index`. `objectgroup` only.
	/* encoding; */                      // Not currently supported.
	int height;                          // Row count. Same as map height for fixed-size maps.
	cute_tiled_layer_t* layers;          // Linked list of layers. Only appears if `type` is `group`.
	cute_tiled_string_t name;            // Name assigned to this layer.
	cute_tiled_object_t* objects;        // Linked list of objects. `objectgroup` only.
	float offsetx;                       // Horizontal layer offset.
	float offsety;                       // Vertical layer offset.
	float opacity;                       // Value between 0 and 1.
	int property_count;                  // Number of elements in the `properties` array.
	cute_tiled_property_t* properties;   // Array of properties.
	int transparentcolor;                // Hex-formatted color (#RRGGBB or #AARRGGBB) (optional).
	int tintcolor;                       // Hex-formatted color (#RRGGBB or #AARRGGBB) (optional).
	cute_tiled_string_t type;            // `tilelayer`, `objectgroup`, `imagelayer` or `group`.
	cute_tiled_string_t image;           // An image filepath. Used if layer is type `imagelayer`.
	int visible;                         // 0 or 1. Whether layer is shown or hidden in editor.
	int width;                           // Column count. Same as map width for fixed-size maps.
	int x;                               // Horizontal layer offset in tiles. Always 0.
	int y;                               // Vertical layer offset in tiles. Always 0.
	float parallaxx;                     // X axis parallax factor.
	float parallaxy;                     // Y axis parallax factor.
	int id;                              // ID of the layer.
	cute_tiled_layer_t* next;            // Pointer to the next layer. NULL if final layer.
};

struct cute_tiled_frame_t
{
	int duration;                        // Frame duration in milliseconds.
	int tileid;                          // Local tile ID representing this frame.
};

struct cute_tiled_tile_descriptor_t
{
	int tile_index;                      // ID of the tile local to the associated tileset.
	cute_tiled_string_t type;            // String assigned to type field in editor.
	int frame_count;                     // The number of animation frames in the `animation` array.
	cute_tiled_frame_t* animation;       // An array of `cute_tiled_frame_t`'s. Can be NULL.
	cute_tiled_string_t image;           // Image used for a tile in a tileset of type collection of images (relative path from map file to source image).
					     // Tileset is a collection of images if image.ptr isn't NULL.
	int imageheight;                     // Image height of a tile in a tileset of type collection of images.
	int imagewidth;                      // Image width of a tile in a tileset of type collection of images.
	cute_tiled_layer_t* objectgroup;     // Linked list of layers of type `objectgroup` only. Useful for holding collision info.
	int property_count;                  // Number of elements in the `properties` array.
	cute_tiled_property_t* properties;   // Array of properties.
	/* terrain */                        // Not currently supported.
	float probability;                   // The probability used when painting with the terrain brush in `Random Mode`.
	cute_tiled_tile_descriptor_t* next;  // Pointer to the next tile descriptor. NULL if final tile descriptor.
};

// IMPORTANT NOTE
// If your tileset is not embedded you will get a warning -- to disable this warning simply define
// this macro CUTE_TILED_NO_EXTERNAL_TILESET_WARNING.
//
// Here is an example.
//
//    #define CUTE_TILED_NO_EXTERNAL_TILESET_WARNING
//    #define CUTE_TILED_IMPLEMENTATION
//    #include <cute_tiled.h>
struct cute_tiled_tileset_t
{
	int backgroundcolor;                 // Hex-formatted color (#RRGGBB or #AARRGGBB) (optional).
	int columns;                         // The number of tile columns in the tileset.
	int firstgid;                        // GID corresponding to the first tile in the set.
	/* grid */                           // Not currently supported.
	cute_tiled_string_t image;           // Image used for tiles in this set (relative path from map file to source image).
	int imagewidth;                      // Width of source image in pixels.
	int imageheight;                     // Height of source image in pixels.
	int margin;                          // Buffer between image edge and first tile (pixels).
	cute_tiled_string_t name;            // Name given to this tileset.
	cute_tiled_string_t objectalignment; // Alignment to use for tile objects (unspecified (default), topleft, top, topright, left, center, right, bottomleft, bottom or bottomright) (since 1.4).
	int property_count;                  // Number of elements in the `properties` array.
	cute_tiled_property_t* properties;   // Array of properties.
	int spacing;                         // Spacing between adjacent tiles in image (pixels).
	/* terrains */                       // Not currently supported.
	int tilecount;                       // The number of tiles in this tileset.
	cute_tiled_string_t tiledversion;    // The Tiled version used to save the tileset.
	int tileheight;                      // Maximum height of tiles in this set.
	int tileoffset_x;                    // Pixel offset to align tiles to the grid.
	int tileoffset_y;                    // Pixel offset to align tiles to the grid.
	cute_tiled_tile_descriptor_t* tiles; // Linked list of tile descriptors. Can be NULL.
	int tilewidth;                       // Maximum width of tiles in this set.
	int transparentcolor;                // Hex-formatted color (#RRGGBB or #AARRGGBB) (optional).
	cute_tiled_string_t type;            // `tileset` (for tileset files, since 1.0).
	cute_tiled_string_t source;          // Relative path to tileset, when saved externally from the map file.
	cute_tiled_tileset_t* next;          // Pointer to next tileset. NULL if final tileset.
	float version;                       // The JSON format version (like 1.2).
	void* _internal;                     // For internal use only. Don't touch.
};

struct cute_tiled_map_t
{
	int backgroundcolor;                 // Hex-formatted color (#RRGGBB or #AARRGGBB) (optional).
	int height;                          // Number of tile rows.
	/* hexsidelength */                  // Not currently supported.
	int infinite;                        // Whether the map has infinite dimensions.
	cute_tiled_layer_t* layers;          // Linked list of layers. Can be NULL.
	int nextobjectid;                    // Auto-increments for each placed object.
	cute_tiled_string_t orientation;     // `orthogonal`, `isometric`, `staggered` or `hexagonal`.
	int property_count;                  // Number of elements in the `properties` array.
	cute_tiled_property_t* properties;   // Array of properties.
	cute_tiled_string_t renderorder;     // Rendering direction (orthogonal maps only).
	/* staggeraxis */                    // Not currently supported.
	/* staggerindex */                   // Not currently supported.
	cute_tiled_string_t tiledversion;    // The Tiled version used to save the file.
	int tileheight;                      // Map grid height.
	cute_tiled_tileset_t* tilesets;      // Linked list of tilesets.
	int tilewidth;                       // Map grid width.
	cute_tiled_string_t type;            // `map` (since 1.0).
	float version;                       // The JSON format version (like 1.2).
	int width;                           // Number of tile columns.
	int nextlayerid;                     // The ID of the following layer.
};

// #define CUTE_TILED_H
// #endif