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
    // ci::gl::BatchRef m_circle_batch;
    ci::TriMesh m_mesh;
    ci::CameraPersp m_cam;
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
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // ci::gl::GlslProgRef solidShader
    // {
    //     ci::gl::GlslProg::create(
    //         // Vertex code
    //         CI_GLSL(
    //             150,
    //             uniform mat4 ciModelViewProjection;

    // in vec4 ciPosition;
    // in vec4 ciColor;

    // out lowp vec4 Color;

    // void main( void ) {
    //     gl_Position = ciModelViewProjection * ciPosition;
    //     Color       = ciColor;
    // } ),
    //// Fragment code
    //CI_GLSL(
    // 150,
    // in vec4 Color;
    // out vec4 oColor;

    // void main( void ) {
    //     oColor = Color;
    // } ) )
    //};

    // ci::ColorAf green( 0, 1, 0 );
    // ci::ColorAf blue( 0, 0, 1 );
    // m_circle_batch = ci::gl::Batch::create(
    //     ci::geom::Rect()
    //         .colors( green, green, blue, blue )
    //         .rect( ci::Rectf( -200, -10, 15, 10 ) ),
    //     solidShader );
    ////////////////////////////////////////////////////////////////////////////////////////////

    ci::gl::enableDepthWrite();
    ci::gl::enableDepthRead();

    m_cam.lookAt( ci::vec3( 250, 200, 500 ), vec3( 0 ) );

    ////////////////////////////////////////////////////////////////////////////////////////////

    // m_mesh = ci::TriMesh(
    //     ci::TriMesh::Format()
    //         .positions()
    //         .colors( 3 ) );

    // auto const append_to_mesh = [ & ]( ci::vec3 const& vec, ci::Color const& color ) {
    //     m_mesh.appendPosition( vec );
    //     m_mesh.appendColorRgb( color );
    // };
    // append_to_mesh( ci::vec3( 10, 10, 0 ), ci::Color( 0, 1, 0 ) );
    // append_to_mesh( ci::vec3( 10, 100, 0 ), ci::Color( 0, 0, 0 ) );
    // append_to_mesh( ci::vec3( 100, 10, 0 ), ci::Color( 1, 1, 0 ) );
    // append_to_mesh( ci::vec3( 100, 100, 0 ), ci::Color( 1, 0, 0 ) );

    // m_mesh.appendTriangle( 1, 3, 2 );
    // m_mesh.appendTriangle( 1, 2, 0 );
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
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ci::gl::clear();

    // for( float angle{}; angle < 2.0F * M_PI; angle += 0.2F )
    // {
    //     ci::gl::ScopedModelMatrix scpModelMtx;
    //     ci::gl::translate(
    //         getWindowCenter() + 200.0F * ci::vec2{ sin( angle ), cos( angle ) } );
    //     ci::gl::color( ci::Color( ci::CM_HSV, angle / ( 2.0F * M_PI ), 1, 1 ) );
    //     m_circle_batch->draw();
    // }

    //////////////////////////////////////////////////////////////////////////////////////
    // ci::gl::clear();
    // ci::gl::draw( m_mesh );
    //////////////////////////////////////////////////////////////////////////////////////

    ci::gl::clear( ci::Color::white() );

    m_mesh = ci::TriMesh(
        ci::TriMesh::Format()
            .positions()
            .colors( 3 ) );

    // Create the points of our cube
    ci::vec3 v0{ -100, -100, -100 };
    ci::vec3 v1{ 100, -100, -100 };
    ci::vec3 v2{ 100, 100, -100 };
    ci::vec3 v3{ -100, 100, -100 };
    ci::vec3 v4{ -100, -100, 100 };
    ci::vec3 v5{ 100, -100, 100 };
    ci::vec3 v6{ 100, 100, 100 };
    ci::vec3 v7{ -100, 100, 100 };

    // Create the colors for each vertex
    ci::Color c0{ 0, 0, 0 };
    ci::Color c1{ 1, 0, 0 };
    ci::Color c2{ 1, 1, 0 };
    ci::Color c3{ 0, 1, 0 };
    ci::Color c4{ 0, 0, 1 };
    ci::Color c5{ 1, 0, 1 };
    ci::Color c6{ 1, 1, 1 };
    ci::Color c7{ 0, 1, 1 };

    std::array < std::array <
}

CINDER_APP( SkipboApp, ci::app::RendererGl, prepareSettings )