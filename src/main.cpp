#include "skipbo.h"
#include "version.h"

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

struct SkipboApp : ci::app::App
{
    void draw() override;
};

void prepareSettings( SkipboApp::Settings* settings )
{
    settings->setMultiTouchEnabled( false );
}

void SkipboApp::draw()
{
    // Clear the contents of the window. This call will clear
    // both the color and depth buffers.
    ci::gl::clear( ci::Color::gray( 0.1f ) );

    // Set the current draw color to orange by setting values for
    // red, green and blue directly. Values range from 0 to 1.
    // See also: gl::ScopedColor
    ci::gl::color( 1.0f, 0.5f, 0.25f );

    // We're going to draw a line through all the points in the list
    // using a few convenience functions: 'begin' will tell OpenGL to
    // start constructing a line strip, 'vertex' will add a point to the
    // line strip and 'end' will execute the draw calls on the GPU.
    ci::gl::begin( GL_LINE_STRIP );
    // for( const vec2 &point : mPoints ) {
    // 	gl::vertex( point );
    // }
    ci::gl::end();
}

// This line tells Cinder to actually create and run the application.
CINDER_APP( SkipboApp, ci::app::RendererGl, prepareSettings )