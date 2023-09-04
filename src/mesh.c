#include <stdio.h>
#include <string.h>

#include "mesh.h"
#include "array.h"

// ===================================================================
// Initialize values
// ===================================================================
vec3_t cube_vertices[N_CUBE_VERTICES] = {
    {-1, -1, -1}, // 1
    {-1, 1, -1},  // 2
    {1, 1, -1},   // 3
    {1, -1, -1},  // 4
    {1, 1, 1},    // 5
    {1, -1, 1},   // 6
    {-1, 1, 1},   // 7
    {-1, -1, 1},  // 8
};
face_t cube_faces[N_CUBE_FACES] = {
    // front
    {1, 2, 3},
    {1, 3, 4},
    // right
    {4, 3, 5},
    {4, 5, 6},
    // back
    {6, 5, 7},
    {6, 7, 8},
    // left
    {8, 7, 2},
    {8, 2, 1},
    // top
    {2, 7, 5},
    {2, 5, 3},
    // bottom
    {6, 8, 1},
    {6, 1, 4},
};

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0, 0, 0}};

// ===================================================================
// Functions
// ===================================================================
void load_cube_mesh_data(void)
{
    // load vertices
    for (int i = 0; i < N_CUBE_VERTICES; i++)
    {
        vec3_t cube_vertex = cube_vertices[i];
        array_push(mesh.vertices, cube_vertex);
    }

    // load faces
    for (int i = 0; i < N_CUBE_VERTICES; i++)
    {
        face_t cube_face = cube_faces[i];
        array_push(mesh.faces, cube_face);
    }
}

/// Read contents of the .obj file and load them into mesh data
void load_obj_file_data(char *filename)
{
    FILE *file;
    file = fopen(filename, "r");

    char line[1024];
    while (fgets(line, 1024, file))
    {
        // get vertex data
        if (strncmp(line, "v ", 2) == 0)
        {
            vec3_t vertex;
            sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            array_push(mesh.vertices, vertex);
        }

        // get face data
        if (strncmp(line, "f ", 2) == 0)
        {
            // note: format is <vertex index>/<texture coords>/<normal indices>
            int vertex_indices[3];
            int texture_indices[3];
            int normal_indices[3];
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                   &vertex_indices[0], &texture_indices[0], &normal_indices[0],
                   &vertex_indices[1], &texture_indices[1], &normal_indices[1],
                   &vertex_indices[2], &texture_indices[2], &normal_indices[2]);
            face_t face = {
                vertex_indices[0],
                vertex_indices[1],
                vertex_indices[2],
            };
            array_push(mesh.faces, face);
        }
    }

    fclose(file);
}