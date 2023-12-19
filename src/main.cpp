#include "skipbo.h"
#include "version.h"

#include <cinder/ImageIo.h>
#include <cinder/ObjLoader.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/VboMesh.h>
#include <cinder/gl/gl.h>

struct SkipboApp : ci::app::App
{
    void setup() override;
    void update() override;
    void draw() override;
    void twirl( ci::Surface* surface, ci::Area area, float maxAngle );

    ci::gl::Texture2dRef m_tex;
};

void prepareSettings( SkipboApp::Settings* const settings )
{
    settings->setMultiTouchEnabled( false );
    settings->setWindowSize( 1280, 960 );
    settings->setFrameRate( 10.0F );
    settings->setTitle( "Skipbo v" + version::GetSemanticVersion() );
}

void SkipboApp::twirl( ci::Surface* const surface, ci::Area const area, float const maxAngle )
{
    ci::Surface const inputSurface{ surface->clone() };

    auto inputIter{ inputSurface.getIter() };
    auto outputIter{ surface->getIter( area ) };

    float maxDistance{ ci::length( static_cast< ci::vec2 >( area.getSize() ) ) / 2.0F };
    ci::ivec2 mid{ ( area.getUL() + area.getLR() ) / 2 };

    while( inputIter.line() && outputIter.line() )
    {
        while( inputIter.pixel() && outputIter.pixel() )
        {
        }
    }
}

void SkipboApp::setup()
{

    ci::gl::enableDepthWrite();
    ci::gl::enableDepthRead();

    auto img{ ci::loadImage( loadAsset( "card-art.png" ) ) };
    ci::Surface bitmap( img );

    ci::Area area( 0, 0, bitmap.getWidth(), bitmap.getHeight() );
    auto iter{ bitmap.getIter( area ) };
    while( iter.line() )
    {
        while( iter.pixel() )
        {
            iter.r() = 255 - iter.r();
            iter.g() = 255 - iter.g();
            iter.b() = 255 - iter.b();
        }
    }
    m_tex = ci::gl::Texture2d::create( bitmap );
}

void SkipboApp::update()
{
}

void SkipboApp::draw()
{
    ci::gl::clear();
    ci::gl::draw( m_tex );
}

CINDER_APP( SkipboApp, ci::app::RendererGl, prepareSettings )