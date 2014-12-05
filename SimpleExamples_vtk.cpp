// vtk_compilado.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

#include <vtkElevationFilter.h>
#include <vtkWarpScalar.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkStructuredPoints.h>
#include <vtkFloatArray.h>

#include <vtkConeSource.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkPoints.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkCellData.h>
#include <vtkProperty.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>

#include <vtkGlyph3D.h>
#include <vtkGlyph3DMapper.h>
#include <vtkArrowSource.h>
#include <vtkCubeSource.h>

#include <vtkInteractorStyle.h>
#include <vtkLine.h>
#include <vtkVersion.h>

#include <vtkCellArray.h>
#include <vtkSmartPointer.h>

#include <vtkSimple2DLayoutStrategy.h>
#include <vtkGlyphSource2D.h>
#include <vtkGraphLayout.h>
#include <vtkGraphLayoutView.h>
#include <vtkGraphToPolyData.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkVersion.h>

#include <vtkDenseArray.h>
#include <vtkArrayToTable.h>
#include <vtkTable.h>
#include <vtkArrayData.h>
#include <vtkAdjacencyMatrixToEdgeTable.h>
#include <vtkArrayPrint.h>

#include <vtkCircularLayoutStrategy.h>
#include <vtkDataSetAttributes.h>
#include <vtkDoubleArray.h>

#include <vtkGraphLayoutView.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkSmartPointer.h>

#include <vtkLight.h>
#include <vtkLightActor.h>
#include <vtkLightCollection.h>
#include <vtkPlaneSource.h>


using namespace std;

void esfera(){
	vtkSphereSource *source = vtkSphereSource::New();
	source->SetRadius(1);
	source->SetPhiResolution(50);
	source->SetThetaResolution(50);

	//Filtro
	vtkElevationFilter *filter = vtkElevationFilter::New();
	filter->SetInputConnection(source->GetOutputPort());
	filter->SetLowPoint(0, 0, -1);
	filter->SetHighPoint(0, 0, 1);

	vtkWarpScalar *filter2 = vtkWarpScalar::New();
	filter2->SetInputConnection(filter->GetOutputPort());
	filter2->SetScaleFactor(2);


	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(filter2->GetOutputPort());

	vtkActor* actor = vtkActor::New();
	actor->SetMapper(mapper);

	//Exibe a janela
	vtkRenderWindow *window = vtkRenderWindow::New();
	vtkRenderer *render = vtkRenderer::New();
	vtkRenderWindowInteractor *interac = vtkRenderWindowInteractor::New();
	window->SetInteractor(interac);
	window->AddRenderer(render);

	render->AddActor(actor);

	interac->Initialize();
	window->Render();
	interac->Start();

	//desaloca tudo
	filter->Delete();
	actor->Delete();
	mapper->Delete();
	source->Delete();
	interac->Delete();
	render->Delete();
	window->Delete();

}

void cubo_estruturado(){

	vtkStructuredPoints *cubo = vtkStructuredPoints::New();
	cubo->SetOrigin(0, 0, 0);
	cubo->SetDimensions(3, 3, 3);
	cubo->SetSpacing(1, 1, 1);

	//criando mapper que recebe o source
	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	//mapper->SetInputConnection(cubo->GetOutputPort());

	//criando actor que vai para o stage (window)
	vtkActor* actor = vtkActor::New();
	actor->SetMapper(mapper);

	//criando window
	vtkRenderWindow *window = vtkRenderWindow::New();
	//criando renderizador
	vtkRenderer *render = vtkRenderer::New();
	//criando interador para renderizar window com o render
	vtkRenderWindowInteractor *interac = vtkRenderWindowInteractor::New();

	window->SetInteractor(interac);
	window->AddRenderer(render);
	render->AddActor(actor);

	interac->Initialize();
	window->Render();
	interac->Start();


	cubo->Delete();
	actor->Delete();
	mapper->Delete();
	interac->Delete();
	render->Delete();
	window->Delete();

}

void cone(){
	
	vtkConeSource *cone_source = vtkConeSource::New();
		cone_source->SetResolution(8);

	vtkConeSource *cone_source2 = vtkConeSource::New();
		cone_source->SetResolution(15);

	//criando mapper que recebe o source
	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(cone_source->GetOutputPort());
	
	vtkPolyDataMapper *mapper2 = vtkPolyDataMapper::New();
	mapper->SetInputConnection(cone_source2->GetOutputPort());

	//criando actor que vai para o stage (window)
	vtkActor* actor = vtkActor::New();
		actor->SetMapper(mapper);

	vtkActor* actor2 = vtkActor::New();
		actor2->SetMapper(mapper2);

	//criando window
	vtkRenderWindow *window = vtkRenderWindow::New();
	//criando renderizador
	vtkRenderer *render = vtkRenderer::New();
	//criando interador para renderizar window com o render
	vtkRenderWindowInteractor *interac = vtkRenderWindowInteractor::New();

	vtkRenderWindow *window2 = vtkRenderWindow::New();
	//criando renderizador
	vtkRenderer *render2 = vtkRenderer::New();
	//criando interador para renderizar window com o render
	vtkRenderWindowInteractor *interac2 = vtkRenderWindowInteractor::New();



	window->SetInteractor(interac);
	window->AddRenderer(render);
	render->AddActor(actor);

	interac->Initialize();
	window->Render();
	interac->Start();

	cone_source->Delete();
	actor->Delete();
	mapper->Delete();
	interac->Delete();
	render->Delete();
	window->Delete();

}

void teste(){
	srand(time(NULL));
	vtkPoints* points = vtkPoints::New();

	vtkIntArray *pointarr = vtkIntArray::New();
	vtkIntArray *pointarr2 = vtkIntArray::New();
	pointarr->SetNumberOfComponents(3);
	for (int j = 0; j<100; j++){
		for (int i = 0; i<100; i++){
			points->InsertNextPoint(i, j, sin(i / 10.) * 10);
			pointarr->InsertNextTuple3(rand() % 100, rand() % 100, rand() % 100);
			pointarr2->InsertNextTuple1(i + j);
		}
	}
	vtkIntArray *arr = vtkIntArray::New();

	for (int j = 0; j<99; j++){
		for (int i = 0; i<99; i++){
			arr->InsertNextTuple1(i + j);
		}
	}

	vtkStructuredGrid *grid = vtkStructuredGrid::New();
	pointarr->SetName("nome2");
	pointarr2->SetName("nome3");
	grid->GetPointData()->AddArray(pointarr);
	grid->GetPointData()->AddArray(pointarr2);
	grid->GetPointData()->SetActiveAttribute("nome2", vtkDataSetAttributes::VECTORS);
	grid->GetPointData()->SetActiveAttribute("nome3", vtkDataSetAttributes::SCALARS);

	arr->SetName("nome");
	grid->GetCellData()->AddArray(arr);
	arr->Delete();
	grid->GetCellData()->SetActiveAttribute("nome", vtkDataSetAttributes::SCALARS);
	grid->SetDimensions(100, 100, 1);
	grid->SetPoints(points);

	vtkStructuredGridGeometryFilter *geo = vtkStructuredGridGeometryFilter::New();
	geo->SetInputData(grid);
	geo->Update();

	vtkArrowSource *arrow = vtkArrowSource::New();
	vtkGlyph3D *glyp = vtkGlyph3D::New();
	glyp->SetSourceConnection(arrow->GetOutputPort());
	glyp->OrientOn();
	glyp->SetVectorModeToUseVector();
	glyp->SetInputConnection(geo->GetOutputPort());
	glyp->SetScaleModeToScaleByVectorComponents();
	glyp->SetScaleFactor(0.01);
	glyp->SetColorModeToColorByScalar();
	glyp->Update();


	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(glyp->GetOutputPort());
	mapper->SetScalarModeToUseCellData();
	mapper->SetScalarRange(0, 200);


	vtkPolyDataMapper *mapper2 = vtkPolyDataMapper::New();
	mapper2->SetInputConnection(geo->GetOutputPort());
	mapper2->SetColorModeToMapScalars();
	mapper2->SetScalarModeToUsePointData();
	mapper2->SetScalarRange(0, 200);


	vtkActor* actor = vtkActor::New();
	actor->SetMapper(mapper);

	vtkActor* actor2 = vtkActor::New();
	actor2->SetMapper(mapper2);

	vtkRenderer *render = vtkRenderer::New();
	vtkRenderWindowInteractor *interact = vtkRenderWindowInteractor::New();

	vtkRenderWindow *win = vtkRenderWindow::New();

	vtkRenderer *render2 = vtkRenderer::New();
	vtkRenderWindowInteractor *interact2 = vtkRenderWindowInteractor::New();

	vtkRenderWindow *win2 = vtkRenderWindow::New();

	win->SetInteractor(interact);
	win->AddRenderer(render);
	render->AddActor(actor);


	interact->Initialize();
	win->Render();
	interact->Start();


	win2->SetInteractor(interact2);
	win2->AddRenderer(render2);
	render2->AddActor(actor2);

	interact2->Initialize();
	win2->Render();
	interact2->Start();
}

void cubo(){
	vtkCubeSource *cube_source = vtkCubeSource::New();

	//criando mapper que recebe o source
	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(cube_source->GetOutputPort());

	//criando actor que vai para o stage (window)
	vtkActor* actor = vtkActor::New();
	actor->SetMapper(mapper);

	//criando window
	vtkRenderWindow *window = vtkRenderWindow::New();
	//criando renderizador
	vtkRenderer *render = vtkRenderer::New();
	//criando interador para renderizar window com o render
	vtkRenderWindowInteractor *interac = vtkRenderWindowInteractor::New();

	window->SetInteractor(interac);
	window->AddRenderer(render);
	render->AddActor(actor);

	interac->Initialize();
	window->Render();
	interac->Start();

	cube_source->Delete();
	actor->Delete();
	mapper->Delete();
	interac->Delete();
	render->Delete();
	window->Delete();
}

void lines(){
	
	double p1[3] = { 0, 0, 0 };
	double p2[3] = { 1, 0, 0 };
	double p3[3] = { 0, 1, 0 };
	vtkPoints *points = vtkPoints::New();
	points->InsertNextPoint(p1);
	points->InsertNextPoint(p2);
	points->InsertNextPoint(p3);


	unsigned char red[3] = { 255, 0, 0 };
	unsigned char blue[3] = { 0, 0, 255 };

	vtkUnsignedCharArray *colors = vtkUnsignedCharArray::New();
	colors->SetNumberOfComponents(3);
	colors->SetName("Colors");

	colors->InsertNextTupleValue(red);
	colors->InsertNextTupleValue(blue);
	 


	//criando mapper que recebe o source
	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	//mapper->SetInputConnection(source->GetOutputPort());

	//criando actor que vai para o stage (window)
	vtkActor* actor = vtkActor::New();
	actor->SetMapper(mapper);

	//criando window
	vtkRenderWindow *window = vtkRenderWindow::New();
	//criando renderizador
	vtkRenderer *render = vtkRenderer::New();
	//criando interador para renderizar window com o render
	vtkRenderWindowInteractor *interac = vtkRenderWindowInteractor::New();

	window->SetInteractor(interac);
	window->AddRenderer(render);
	render->AddActor(actor);

	interac->Initialize();
	window->Render();
	interac->Start();

	//source->Delete();
	actor->Delete();
	mapper->Delete();
	interac->Delete();
	render->Delete();
	window->Delete();

}

void graph(){
	vtkSmartPointer<vtkMutableUndirectedGraph> g =
		vtkSmartPointer<vtkMutableUndirectedGraph>::New();

	vtkIdType v1 = g->AddVertex();
	vtkIdType v2 = g->AddVertex();
	vtkIdType v3 = g->AddVertex();
	vtkIdType v4 = g->AddVertex();
	vtkIdType v5 = g->AddVertex();
	vtkIdType v6 = g->AddVertex();
	vtkIdType v7 = g->AddVertex();
	vtkIdType v8 = g->AddVertex();
	vtkIdType v9 = g->AddVertex();
	g->AddEdge(v1, v2); g->AddEdge(v2, v3); g->AddEdge(v3, v5); g->AddEdge(v5, v6); g->AddEdge(v6, v7); g->AddEdge(v7, v8); g->AddEdge(v8, v9); g->AddEdge(v9, v1);
	g->AddEdge(v3, v4); g->AddEdge(v3, v4); g->AddEdge(v3, v4); g->AddEdge(v3, v4); g->AddEdge(v3, v4); g->AddEdge(v3, v4); g->AddEdge(v3, v4); g->AddEdge(v3, v4);
	g->AddEdge(v4, v7); g->AddEdge(v4, v7); g->AddEdge(v4, v7); g->AddEdge(v4, v7); g->AddEdge(v4, v7); g->AddEdge(v4, v7); g->AddEdge(v4, v7); g->AddEdge(v4, v7);
	g->AddEdge(v4, v8); g->AddEdge(v4, v8); g->AddEdge(v4, v8); g->AddEdge(v4, v8); g->AddEdge(v4, v8); g->AddEdge(v4, v8); g->AddEdge(v4, v8); g->AddEdge(v4, v8);
	g->AddEdge(v2, v4); g->AddEdge(v2, v4); g->AddEdge(v2, v4); g->AddEdge(v2, v4); g->AddEdge(v2, v4); g->AddEdge(v2, v4); g->AddEdge(v2, v4); g->AddEdge(v2, v4);
	g->AddEdge(v4, v1); g->AddEdge(v4, v1); g->AddEdge(v4, v1); g->AddEdge(v4, v1); g->AddEdge(v4, v1); g->AddEdge(v4, v1); g->AddEdge(v4, v1); g->AddEdge(v4, v1);
	g->AddEdge(v4, v6); g->AddEdge(v4, v6); g->AddEdge(v4, v6); g->AddEdge(v4, v6); g->AddEdge(v4, v6); g->AddEdge(v4, v6); g->AddEdge(v4, v6); g->AddEdge(v4, v6);
	g->AddEdge(v4, v9); g->AddEdge(v4, v9); g->AddEdge(v4, v9); g->AddEdge(v4, v9); g->AddEdge(v4, v9); g->AddEdge(v4, v9); g->AddEdge(v4, v9); g->AddEdge(v4, v9);
	g->AddEdge(v4, v5); g->AddEdge(v4, v5); g->AddEdge(v4, v5); g->AddEdge(v4, v5); g->AddEdge(v4, v5); g->AddEdge(v4, v5); g->AddEdge(v4, v5); g->AddEdge(v4, v5);
	vtkSmartPointer<vtkGraphLayoutView> graphLayoutView =
		vtkSmartPointer<vtkGraphLayoutView>::New();

	graphLayoutView->AddRepresentationFromInput(g);
	graphLayoutView->ResetCamera();
	graphLayoutView->Render();
	graphLayoutView->GetInteractor()->Start();

}

void polygraph(){

	// Create a graph
	vtkSmartPointer<vtkMutableUndirectedGraph> g =
		vtkSmartPointer<vtkMutableUndirectedGraph>::New();

	// Add 4 vertices to the graph
	vtkIdType v1 = g->AddVertex();
	vtkIdType v2 = g->AddVertex();
	vtkIdType v3 = g->AddVertex();
	vtkIdType v4 = g->AddVertex();
	vtkIdType v5 = g->AddVertex();
	vtkIdType v6 = g->AddVertex();
	vtkIdType v7 = g->AddVertex();
	vtkIdType v8 = g->AddVertex();

	// Add 3 edges to the graph
	g->AddEdge(v1, v2);
	g->AddEdge(v3, v4);
	g->AddEdge(v2, v4);
	g->AddEdge(v3, v1);
	
	g->AddEdge(v1, v5);
	g->AddEdge(v2, v6);
	g->AddEdge(v3, v7);
	g->AddEdge(v4, v8);
	
	g->AddEdge(v5, v6);
	g->AddEdge(v7, v8);
	g->AddEdge(v6, v8);
	g->AddEdge(v7, v5);

	// Create 4 points - one for each vertex
	vtkSmartPointer<vtkPoints> points =
		vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0.0, 0.0, 0.0);
	points->InsertNextPoint(1.0, 0.0, 0.0);
	points->InsertNextPoint(0.0, 1.0, 0.0);
	points->InsertNextPoint(1.0, 1.0, 0.0);
	
	points->InsertNextPoint(0.0, 0.0, 1.0);
	points->InsertNextPoint(1.0, 0.0, 1.0);
	points->InsertNextPoint(0.0, 1.0, 1.0);
	points->InsertNextPoint(1.0, 1.0, 1.0);
	// Add the coordinates of the points to the graph
	g->SetPoints(points);

	// Convert the graph to a polydata
	vtkSmartPointer<vtkGraphToPolyData> graphToPolyData =
		vtkSmartPointer<vtkGraphToPolyData>::New();
	graphToPolyData->SetInputData(g);
	graphToPolyData->Update();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(graphToPolyData->GetOutputPort());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	// Create a renderer, render window, and interactor
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	// Add the actor to the scene
	renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3); // Background color green

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();

}

void luz(){

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	double lightPosition[3] = { 0, 0, 1 };

	// Create a light
	double lightFocalPoint[3] = { 0, 0, 0 };

	vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
	light->SetLightTypeToSceneLight();
	light->SetPosition(lightPosition[0], lightPosition[1], lightPosition[2]);
	light->SetPositional(true); // required for vtkLightActor below
	light->SetConeAngle(10);
	light->SetFocalPoint(lightFocalPoint[0], lightFocalPoint[1], lightFocalPoint[2]);
	light->SetDiffuseColor(1, 0, 0);
	light->SetAmbientColor(0, 1, 0);
	light->SetSpecularColor(0, 0, 1);

	vtkLightCollection* originalLights = renderer->GetLights();
	cout << "Originally there are " << originalLights->GetNumberOfItems() << " lights." << std::endl;

	//  renderer->AddLight(light); // can't do this here - must do this after the renderWindow->Render() below

	// Display where the light is
	vtkSmartPointer<vtkLightActor> lightActor = vtkSmartPointer<vtkLightActor>::New();
	lightActor->SetLight(light);
	renderer->AddViewProp(lightActor);

	// Display where the light is focused
	vtkSmartPointer<vtkSphereSource> lightFocalPointSphere = vtkSmartPointer<vtkSphereSource>::New();
	lightFocalPointSphere->SetCenter(lightFocalPoint);
	lightFocalPointSphere->SetRadius(.1);
	lightFocalPointSphere->Update();

	vtkSmartPointer<vtkPolyDataMapper> lightFocalPointMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	lightFocalPointMapper->SetInputConnection(lightFocalPointSphere->GetOutputPort());

	vtkSmartPointer<vtkActor> lightFocalPointActor = vtkSmartPointer<vtkActor>::New();
	lightFocalPointActor->SetMapper(lightFocalPointMapper);
	lightFocalPointActor->GetProperty()->SetColor(1.0, 1.0, 0.0); //(R,G,B)
	renderer->AddViewProp(lightFocalPointActor);

	// Create a plane for the light to shine on
	vtkSmartPointer<vtkPlaneSource> planeSource = vtkSmartPointer<vtkPlaneSource>::New();
	planeSource->SetResolution(100, 100);
	planeSource->Update();

	vtkSmartPointer<vtkPolyDataMapper> planeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
	planeMapper->SetInput(planeSource->GetOutput());
#else
	planeMapper->SetInputData(planeSource->GetOutput());
#endif

	vtkSmartPointer<vtkActor> planeActor = vtkSmartPointer<vtkActor>::New();
	planeActor->SetMapper(planeMapper);
	renderer->AddActor(planeActor);

	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	std::cout << "Now there are " << originalLights->GetNumberOfItems() << " lights." << std::endl;


	renderer->AddLight(light); // must do this after renderWindow->Render();
	std::cout << "Now there are " << originalLights->GetNumberOfItems() << " lights." << std::endl;


	renderWindowInteractor->Start();


}

int main(int argc, char * argv[]){

	//esfera();
//	cone();
	//teste();
	//cubo();
	//graph();
	//polygraph();
	//luz();
	
	
	system("PAUSE");
	return 0;
}

