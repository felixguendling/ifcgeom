#include "cinder/CameraUi.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cista/mmap.h"

#include "IFC2X3/IfcRepresentationItem.h"
#include "IFC2X3/IfcShapeRepresentation.h"
#include "IFC2X3/parser.h"

class MyApp : public ci::app::App {
  void setup() override {
    auto const ifc = cista::mmap{"/home/felix/Downloads/Wand_ArchiCad_BRep.ifc"
                                 //"../AC20-Institute-Var-2.ifc"
                                 ,
                                 cista::mmap::protection::READ};
    auto const model = IFC2X3::parse({ifc.data(), ifc.size()});
    for (auto const& e : model.entity_mem_) {
      auto const sr =
          dynamic_cast<IFC2X3::IfcShapeRepresentation const*>(e.get());
      if (sr == nullptr) {
        continue;
      }

      for (auto const& item : sr->Items_) {
        std::cout << item->name() << "\n";
      }
    }

    auto const color = ci::gl::getStockShader(ci::gl::ShaderDef().color());
    cam_.lookAt(glm::vec3{2.0F, 3.0F, 1.0F}, glm::vec3{0});
    cam_.setPerspective(40.0F, getWindowAspectRatio(), 0.01f, 100.0F);
    cam_ui_ = ci::CameraUi(&cam_, getWindow());
    cube_ = ci::gl::Batch::create(ci::geom::WireCube{}, color);
    wire_plane_ = ci::gl::Batch::create(
        ci::geom::WirePlane().size(glm::vec2(10)).subdivisions(glm::ivec2(10)),
        color);
  }

  void draw() override {
    ci::gl::clear(ci::Color::white());
    ci::gl::ScopedMatrices push;
    ci::gl::setMatrices(cam_);

    {
      ci::gl::ScopedColor color(ci::Color::gray(0.2f));
      wire_plane_->draw();
    }

    {
      ci::gl::ScopedColor clr(ci::Color(1, 0.5f, 0));
      ci::gl::ScopedModelMatrix model;
      cube_->draw();
    }
  }

  ci::CameraPersp cam_;
  ci::CameraUi cam_ui_;
  ci::gl::BatchRef cube_;
  ci::gl::BatchRef wire_plane_;
};

CINDER_APP(MyApp, ci::app::RendererGl(ci::app::RendererGl::Options().msaa(8)))
