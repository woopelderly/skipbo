#include "skipbo.h"
#include "version.h"

#include <cinder/ImageIo.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/gl.h>

struct SkipboApp : ci::app::App
{
    void setup() override;
    void update() override;
    void draw() override;

    // ci::gl::Texture2dRef m_my_image;
};

void prepareSettings( SkipboApp::Settings* const settings )
{
    settings->setMultiTouchEnabled( false );
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 30.0F );
    settings->setTitle( "Skipbo v" + version::GetSemanticVersion() );
}

void SkipboApp::setup()
{
    // m_my_image = ci::gl::Texture::create( cinder::loadImage( loadResource( "res/Costa-Rican-Frog.jpg" ) ) );
}

void SkipboApp::update()
{
}

void SkipboApp::draw()
{
    // float const gray_value = sin( getElapsedFrames() ) * 0.5F + 0.5F;
    // ci::gl::clear( ci::Color( gray_value, gray_value, gray_value ), true );

    // ci::gl::draw( m_my_image, getWindowBounds() );
}

CINDER_APP( SkipboApp, ci::app::RendererGl, prepareSettings )