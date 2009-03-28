// -*- mode: c++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998, 1999, 2000  Chris Morley
// Copyright 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007  Braden McDaniel
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, see <http://www.gnu.org/licenses/>.
//

# ifndef OPENVRML_GL_VIEWER_H
#   define OPENVRML_GL_VIEWER_H

#   include <openvrml-gl-common.h>
#   include <openvrml/viewer.h>
#   if OPENVRML_GL_HAVE_WINDOWS_H && defined(_WIN32)
#     include <windows.h>
#   endif
#   if OPENVRML_GL_HAVE_GL_GLU_H
#     include <GL/gl.h>
#     include <GL/glu.h>
#   elif OPENVRML_GL_HAVE_OPENGL_GLU_H
#     include <OpenGL/gl.h>
#     include <OpenGL/glu.h>
#   else
#     error must define OPENVRML_GL_HAVE_GL_GLU_H or OPENVRML_GL_HAVE_OPENGL_GLU_H
#   endif
#   include <stack>

namespace openvrml {

    namespace gl {

        class OPENVRML_GL_API viewer : public openvrml::viewer {
        public:
            enum { max_lights = 8 };

            enum light_type {
                light_unused,
                light_directional,
                light_positional
            };

            enum event_type {
                event_key_down,
                event_mouse_move,
                event_mouse_click,
                event_mouse_drag,
                event_mouse_release
            };

            enum {
                key_home,
                key_left,
                key_up,
                key_right,
                key_down,
                key_page_up,
                key_page_down
            };

            struct event_info {
                event_type event;
                int what;
                int x, y;
            };

        protected:
            enum cursor_style {
                cursor_inherit,
                cursor_info,
                cursor_cycle,
                cursor_up_down,
                cursor_crosshair
            };

            class OPENVRML_LOCAL modelview_matrix_stack {
                size_t size;
                std::stack<mat4f> spillover;

            public:
                modelview_matrix_stack();

                void push();
                void pop();
            };

            struct light_info {
                light_type type;
                int nesting_level;
                float radius_squared;
                vec3f location;
            };

            modelview_matrix_stack modelview_matrix_stack_;

            bool gl_initialized;
            bool blend;
            bool lit;
            bool texture;
            bool wireframe;

            size_t win_width;
            size_t win_height;
            color background;

            size_t objects, nested_objects;

            GLUtesselator * tesselator;

            size_t sensitive;
            size_t active_sensitive;
            size_t over_sensitive;

            enum { maxsensitive = 1000 };
            node * sensitive_object[maxsensitive];

            bool select_mode;
            double select_z;

            light_info light_info_[max_lights];

            int beginx, beginy;

            bool rotating, scaling, translating;
            bool draw_bounding_spheres;

            double render_time;
            double render_time1;

            // Initialize OpenGL state
            void initialize();

            void begin_geometry();
            void end_geometry();

            void step(float, float, float);
            void zoom(float);
            void rotate(const openvrml::rotation & rot) OPENVRML_NOTHROW;

            void handleKey(int);
            void handleButton(event_info * e);
            void handleMouseDrag(int, int);

            // Check for pickable entity selection
            bool checkSensitive(int x, int y, event_type event);

        public:
            viewer();
            virtual ~viewer() OPENVRML_NOTHROW;

            //
            // Viewer callbacks (not for public consumption)

            // Update the model.
            void update( double time = 0.0 );

            // Redraw the screen.
            virtual void redraw();
            void resize(size_t width, size_t height);

            // user interaction

            void input(event_info * e);

        private:
            virtual rendering_mode do_mode();
            virtual double do_frame_rate();

            virtual void do_reset_user_navigation();

            // Scope dirlights, open/close display lists
            virtual object_t do_begin_object(const char * id, bool retain);
            virtual void do_end_object();

            // Insert objects into the display list
            virtual object_t
                do_insert_background(const std::vector<float> & groundAngle,
                                     const std::vector<color> & groundColor,
                                     const std::vector<float> & skyAngle,
                                     const std::vector<color> & skyColor,
                                     const image & front,
                                     const image & back,
                                     const image & left,
                                     const image & right,
                                     const image & top,
                                     const image & bottom);


            virtual object_t do_insert_box(const vec3f & size);
            virtual object_t do_insert_cone(float height, float radius,
                                            bool bottom, bool side);
            virtual object_t do_insert_cylinder(float height, float radius,
                                                bool bottom, bool side,
                                                bool top);

            virtual object_t
                do_insert_elevation_grid(unsigned int mask,
                                         const std::vector<float> & height,
                                         int32 xDimension,
                                         int32 zDimension,
                                         float xSpacing,
                                         float zSpacing,
                                         const std::vector<color> & color,
                                         const std::vector<vec3f> & normal,
                                         const std::vector<vec2f> & texCoord);
            virtual object_t
                do_insert_extrusion(
                    unsigned int mask,
                    const std::vector<vec3f> & spine,
                    const std::vector<vec2f> & crossSection,
                    const std::vector<openvrml::rotation> & orientation,
                    const std::vector<vec2f> & scale);
            virtual object_t
                do_insert_line_set(const std::vector<vec3f> & coord,
                                   const std::vector<int32> & coordIndex,
                                   bool colorPerVertex,
                                   const std::vector<color> & color,
                                   const std::vector<int32> & colorIndex);
            virtual object_t
                do_insert_point_set(const std::vector<vec3f> & coord,
                                    const std::vector<color> & color);
            virtual object_t
                do_insert_shell(unsigned int mask,
                                const std::vector<vec3f> & coord,
                                const std::vector<int32> & coordIndex,
                                const std::vector<color> & color,
                                const std::vector<int32> & colorIndex,
                                const std::vector<vec3f> & normal,
                                const std::vector<int32> & normalIndex,
                                const std::vector<vec2f> & texCoord,
                                const std::vector<int32> & texCoordIndex);
            virtual object_t do_insert_sphere(float radius);

            // Lights
            virtual object_t do_insert_dir_light(float ambientIntensity,
                                                 float intensity,
                                                 const color & color,
                                                 const vec3f & direction);
            virtual object_t do_insert_point_light(float ambientIntensity,
                                                   const vec3f & attenuation,
                                                   const color & color,
                                                   float intensity,
                                                   const vec3f & location,
                                                   float radius);
            virtual object_t do_insert_spot_light(float ambientIntensity,
                                                  const vec3f & attenuation,
                                                  float beamWidth,
                                                  const color & color,
                                                  float cutOffAngle,
                                                  const vec3f & direction,
                                                  float intensity,
                                                  const vec3f & location,
                                                  float radius);


            virtual object_t do_insert_reference(object_t existing_object);

            virtual void do_remove_object(object_t ref);

            virtual void do_enable_lighting(bool);

            // Set attributes
            virtual void do_set_color(const color & rgb, float a = 1.0);

            virtual void do_set_fog(const color & color,
                                    float visibilityRange,
                                    const char * type);

            virtual void do_set_material(float ambientIntensity,
                                         const color & diffuseColor,
                                         const color & emissiveColor,
                                         float shininess,
                                         const color & specularColor,
                                         float transparency);

            virtual void do_set_material_mode(size_t tex_components,
                                              bool geometry_color);

            virtual void do_set_sensitive(node * object);

            virtual texture_object_t
                do_insert_texture(const image & img,
                                  bool repeat_s,
                                  bool repeat_t,
                                  bool retainHint = false);

            // Reference/remove a texture object
            virtual void do_insert_texture_reference(texture_object_t ref,
                                                     size_t components);
            virtual void do_remove_texture_object(texture_object_t);

            virtual void do_set_texture_transform(const vec2f & center,
                                                  float rotation,
                                                  const vec2f & scale,
                                                  const vec2f & translation);

            virtual void do_set_frustum(float field_of_view,
                                        float avatar_size,
                                        float visibility_limit);
            virtual void do_set_viewpoint(const vec3f & position,
                                          const openvrml::rotation & orientation,
                                          float avatarSize,
                                          float visibilityLimit);

            virtual void do_transform(const mat4f & mat);

            virtual void do_transform_points(size_t nPoints,
                                             vec3f * point) const;

            virtual void
                do_draw_bounding_sphere(
                    const bounding_sphere & bs,
                    bounding_volume::intersection intersection);

            // Window system specific methods

            virtual void post_redraw() = 0;
            virtual void set_cursor(cursor_style c) = 0;
            virtual void swap_buffers() = 0;
            virtual void set_timer(double interval) = 0;
        };
    }
}

# endif // OPENVRML_GL_VIEWER_H
