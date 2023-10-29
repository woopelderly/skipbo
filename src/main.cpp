#include "skipbo.h"
#include "version.h"

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

struct SkipboApp : ci::app::App
{
    void setup() override;
    void update() override;
    void draw() override;
};

void prepareSettings( SkipboApp::Settings* settings )
{
    settings->setMultiTouchEnabled( false );
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 30.0F );
}

void SkipboApp::setup()
{
}

void SkipboApp::update()
{
}

void SkipboApp::draw()
{
    float gray = sin( getElapsedFrames() ) * 0.5F + 0.5F;
    ci::gl::clear( ci::Color( gray, gray, gray ), true );
}

CINDER_APP( SkipboApp, ci::app::RendererGl, prepareSettings )