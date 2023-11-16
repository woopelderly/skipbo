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
    ci::gl::BatchRef m_circle_batch;
};

void prepareSettings( SkipboApp::Settings* const settings )
{
    settings->setMultiTouchEnabled( false );
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 10.0F );
    settings->setTitle( "Skipbo v" + version::GetSemanticVersion() );
}

void SkipboApp::setup()
{
    // m_my_image = ci::gl::Texture::create( cinder::loadImage( loadResource( "res/Costa-Rican-Frog.jpg" ) ) );
    // ci::gl::GlslProgRef solidShader{ ci::gl::getStockShader( ci::gl::ShaderDef().color() ) };
    // GlslProgRef solidShader = gl::GlslProg::create(
    //     loadAsset( "solidColor.vert" ),
    //     loadAsset( "solidColor.frag" ) );

    ci::gl::GlslProgRef solidShader
    {
        ci::gl::GlslProg::create(
            // Vertex code
            CI_GLSL(
                150,
                uniform mat4 ciModelViewProjection;

                in vec4 ciPosition;
                in vec4 ciColor;

                out lowp vec4 Color;

                void main( void ) {
                    gl_Position = ciModelViewProjection * ciPosition;
                    Color       = ciColor;
                } ),
            // Fragment code
            CI_GLSL(
                150,
                in vec4 Color;
                out vec4 oColor;

                void main( void ) {
                    oColor = Color;
                } ) )
    };

    ci::ColorAf green( 0, 1, 0 );
    ci::ColorAf blue( 0, 0, 1 );
    m_circle_batch = ci::gl::Batch::create(
        ci::geom::Rect()
            .colors( green, green, blue, blue )
            .rect( ci::Rectf( -200, -10, 15, 10 ) ),
        solidShader );
}

void SkipboApp::update()
{
    // ci::gl::bindStockShader( ci::gl::ShaderDef().color() );
    // ci::gl::color( 1, 0, 0 );
    // ci::gl::drawSolidCircle( ci::vec2( 100, 100 ), 50 );
}

void SkipboApp::draw()
{
    // float const gray_value = sin( getElapsedFrames() ) * 0.5F + 0.5F;
    // ci::gl::clear( ci::Color( gray_value, gray_value, gray_value ), true );

    // ci::gl::draw( m_my_image, getWindowBounds() );

    ci::gl::clear();

    for( float angle{}; angle < 2.0F * M_PI; angle += 0.2F )
    {
        ci::gl::ScopedModelMatrix scpModelMtx;
        ci::gl::translate(
            getWindowCenter() + 200.0F * ci::vec2{ sin( angle ), cos( angle ) } );
        ci::gl::color( ci::Color( ci::CM_HSV, angle / ( 2.0F * M_PI ), 1, 1 ) );
        m_circle_batch->draw();
    }
}

CINDER_APP( SkipboApp, ci::app::RendererGl, prepareSettings )