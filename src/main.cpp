#include "skipbo.h"
#include "version.h"

#include <cinder/ImageIo.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/gl.h>

#include <array>
#include <iostream>

struct SkipboApp : ci::app::App
{
    void setup() override;
    void update() override;
    void draw() override;

    void append_to_mesh( ci::vec3 const& vec, ci::Color const& color );

    // ci::gl::Texture2dRef m_my_image;
    // ci::gl::BatchRef m_circle_batch;
    ci::TriMesh m_mesh;
    ci::CameraPersp m_cam;
};

void prepareSettings( SkipboApp::Settings* const settings )
{
    settings->setMultiTouchEnabled( false );
    settings->setWindowSize( 640, 480 );
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

    m_cam.lookAt( ci::vec3( 250, 200, 500 ), ci::vec3( 0 ) );

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

void SkipboApp::append_to_mesh( ci::vec3 const& vec, ci::Color const& color )
{
    m_mesh.appendPosition( vec );
    m_mesh.appendColorRgb( color );
}

void SkipboApp::update()
{
    // ci::gl::bindStockShader( ci::gl::ShaderDef().color() );
    // ci::gl::color( 1, 0, 0 );
    // ci::gl::drawSolidCircle( ci::vec2( 100, 100 ), 50 );

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto const numberVertices{ m_mesh.getNumVertices() };
    if( numberVertices == 0 )
    {
        std::cerr << "vertices is zero\n";
        return;
    }

    ci::Color* const col{ m_mesh.getColors< 3 >() };
    ci::vec3* const vec{ m_mesh.getPositions< 3 >() };

    std::size_t j{};

    m_mesh.clear();

    float const sinInc{ static_cast< float >( sin( getElapsedSeconds() ) ) };
    float const cosInc{ static_cast< float >( cos( getElapsedSeconds() ) ) };

    while( j < numberVertices )
    {
        auto const mult{ 30.0F };
        vec[ j ].x -= sinInc;
        vec[ j + 1 ].x += sinInc;
        vec[ j + 2 ].x += sinInc * mult;
        vec[ j + 3 ].x -= sinInc * mult;
        vec[ j ].y -= cosInc;
        vec[ j + 1 ].y += cosInc;
        vec[ j + 2 ].y += cosInc * mult;
        vec[ j + 3 ].y -= cosInc * mult;

        append_to_mesh( vec[ j ], col[ j ] );
        append_to_mesh( vec[ j + 1 ], col[ j + 1 ] );
        append_to_mesh( vec[ j + 2 ], col[ j + 2 ] );
        append_to_mesh( vec[ j + 3 ], col[ j + 3 ] );

        auto const vIdx0{ j };
        auto const vIdx1{ j + 1 };
        auto const vIdx2{ j + 2 };
        auto const vIdx3{ j + 3 };

        m_mesh.appendTriangle( vIdx0, vIdx1, vIdx2 );
        m_mesh.appendTriangle( vIdx0, vIdx2, vIdx3 );

        j += 4;
    }
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

    // clang-format off
    // Create the points of our cube
    ci::vec3 constexpr v0{ -100, -100, -100 };
    ci::vec3 constexpr v1{  100, -100, -100 };
    ci::vec3 constexpr v2{  100,  100, -100 };
    ci::vec3 constexpr v3{ -100,  100, -100 };
    ci::vec3 constexpr v4{ -100, -100,  100 };
    ci::vec3 constexpr v5{  100, -100,  100 };
    ci::vec3 constexpr v6{  100,  100,  100 };
    ci::vec3 constexpr v7{ -100,  100,  100 };
    // clang-format on

    // Create the colors for each vertex
    ci::Color const c0{ 0, 0, 0 };
    ci::Color const c1{ 1, 0, 0 };
    ci::Color const c2{ 1, 1, 0 };
    ci::Color const c3{ 0, 1, 0 };
    ci::Color const c4{ 0, 0, 1 };
    ci::Color const c5{ 1, 0, 1 };
    ci::Color const c6{ 1, 1, 1 };
    ci::Color const c7{ 0, 1, 1 };

    // clang-format off
    std::array< std::array< ci::vec3, 4 >, 6 > constexpr faces{ { 
        { v0, v1, v2, v3 }, { v3, v2, v6, v7 }, { v7, v6, v5, v4 }, 
        { v4, v5, v1, v0 }, { v5, v6, v2, v1 }, { v7, v4, v0, v3 } 
    } };

    std::array< std::array< ci::Color, 4 >, 6> colors { {
        {c0, c1, c2, c3}, {c3, c2, c6, c7}, {c7, c6, c5, c4},
        {c4, c5, c1, c0}, {c5, c6, c2, c1}, {c7, c4, c0, c3}
    } };
    // clang-format on

    for( int i{}; i < 6; ++i )
    {
        append_to_mesh( faces.at( i ).at( 0 ), colors.at( i ).at( 0 ) );
        append_to_mesh( faces.at( i ).at( 1 ), colors.at( i ).at( 1 ) );
        append_to_mesh( faces.at( i ).at( 2 ), colors.at( i ).at( 2 ) );
        append_to_mesh( faces.at( i ).at( 3 ), colors.at( i ).at( 3 ) );

        auto const numberVertices{ m_mesh.getNumVertices() };

        // std::cerr << "numberVertices: " << numberVertices << '\n';

        m_mesh.appendTriangle( numberVertices - 4,
                               numberVertices - 3,
                               numberVertices - 2 );

        m_mesh.appendTriangle( numberVertices - 4,
                               numberVertices - 2,
                               numberVertices - 1 );
    }

    update();

    ci::gl::setMatrices( m_cam );
    // ci::gl::ScopedModelMatrix matrix;
    ci::gl::pushModelView();
    ci::gl::draw( m_mesh );
    ci::gl::popModelView();
}

CINDER_APP( SkipboApp, ci::app::RendererGl, prepareSettings )