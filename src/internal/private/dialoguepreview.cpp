#include <public/dialoguepreview.h>
#include "ui_dialoguepreview.h"
#include <public/GraphEditor/TextData.hpp>
#include <public/GraphEditor/GraphBeginDataModel.hpp>
#include <public/GraphEditor/GraphFinishDataModel.hpp>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/NodeStyle>
#include <nodes/FlowViewStyle>
#include <nodes/ConnectionStyle>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;

DialoguePreview::DialoguePreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialoguePreview)
{
    ui->setupUi(this);
}

DialoguePreview::~DialoguePreview()
{
    delete ui;
}

std::shared_ptr<DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

  ret->registerModel<GraphBeginDataModel>();
  ret->registerModel<GraphFinishDataModel>();
  ret->registerModel<TextSourceDataModel>();
  ret->registerModel<TextDisplayDataModel>();

  return ret;
}

static
void
_setStyle()
{
  ConnectionStyle::setConnectionStyle(
    R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");

  //FlowViewStyle::setStyle(
  //R"(
  //{
  //  "FlowViewStyle": {
  //    "BackgroundColor": [255, 255, 240],
  //    "FineGridColor": [245, 245, 230],
  //    "CoarseGridColor": [235, 235, 220]
  //  }
  //}
  //)");
  //
  //NodeStyle::setNodeStyle(
  //R"(
  //{
  //  "NodeStyle": {
  //    "NormalBoundaryColor": "darkgray",
  //    "SelectedBoundaryColor": "deepskyblue",
  //    "GradientColor0": "mintcream",
  //    "GradientColor1": "mintcream",
  //    "GradientColor2": "mintcream",
  //    "GradientColor3": "mintcream",
  //    "ShadowColor": [200, 200, 200],
  //    "FontColor": [10, 10, 10],
  //    "FontColorFaded": [100, 100, 100],
  //    "ConnectionPointColor": "white",
  //    "PenWidth": 2.0,
  //    "HoveredPenWidth": 2.5,
  //    "ConnectionPointDiameter": 10.0,
  //    "Opacity": 1.0,
  //    "padding": 50.0,
  //    "margin": 50.0
  //  }
  //}
  //)");
  //
  //ConnectionStyle::setConnectionStyle(
  //R"(
  //{
  //  "ConnectionStyle": {
  //    "ConstructionColor": "gray",
  //    "NormalColor": "black",
  //    "SelectedColor": "gray",
  //    "SelectedHaloColor": "deepskyblue",
  //    "HoveredColor": "deepskyblue",
  //    "LineWidth": 3.0,
  //    "ConstructionLineWidth": 2.0,
  //    "PointDiameter": 10.0,
  //    "UseDataDefinedColors": false
  //  }
  //}
  //)");
}

void DialoguePreview::on_btnEdit_clicked()
{
    _setStyle();
    FlowScene scene(registerDataModels());

    FlowView view(&scene);

    view.setWindowTitle("Node-based flow editor");
    view.resize(800, 600);
    view.show();

    QEventLoop loop;
    connect(&view, SIGNAL(done()), &loop, SLOT(quit()));
    loop.exec(); // BLOCKING (non-busy) until quit() is called via the signal done()
}
