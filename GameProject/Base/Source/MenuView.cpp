#include "MenuView.h"

MenuView::MenuView(Model* model) : View(model)
{
}

MenuView::~MenuView()
{
}

void MenuView::Render()
{
	View::Render();

	MenuModel *model = dynamic_cast<MenuModel *>(m_model);

	int windowWidth, windowHeight;
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	modelStack.PushMatrix(); {
		modelStack.Translate(-50, 0, -50);
		modelStack.Scale(windowWidth, windowHeight, 1);
		Render2DMesh(model->getMenuMesh(), false);
	} modelStack.PopMatrix();

	if ( !model->getIsSelectingLevels() )
	{
		if ( !model->m_credits )
		{
			modelStack.PushMatrix();
			modelStack.Translate( 0.284f * windowWidth, 0.3f * windowHeight, 1);
			modelStack.Scale(384, 33, 1);
			Render2DMesh(model->getstartBtn(), false);
			modelStack.PopMatrix();

			modelStack.PushMatrix(); 
			modelStack.Translate( 0.284f * windowWidth, 0.25f * windowHeight, 1);
			modelStack.Scale(384, 33, 1);
			Render2DMesh(model->getloadBtn(), false);
			modelStack.PopMatrix();

			modelStack.PushMatrix(); 
			modelStack.Translate( 0.284f * windowWidth, 0.2f * windowHeight, 1);
			modelStack.Scale(384, 33, 1);
			Render2DMesh(model->getcreditsBtn(), false);
			modelStack.PopMatrix();

			modelStack.PushMatrix(); 
			modelStack.Translate( 0.284f * windowWidth, 0.15f * windowHeight, 1);
			modelStack.Scale(384, 33, 1);
			Render2DMesh(model->getexitBtn(), false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			MenuModel* model = dynamic_cast<MenuModel *>(m_model);
			int windowWidth, windowHeight;
			glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
			std::ostringstream ss;
			ss << getHighScore();
			RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 60, windowWidth * 0.65, windowHeight * 0.3);
			modelStack.PopMatrix();
		}
	}
	else
	{
		modelStack.PushMatrix(); 
		modelStack.Translate( 0.284f * windowWidth, 0.3f * windowHeight, 1);
		modelStack.Scale(384, 33, 1);
		Render2DMesh(model->getLv1(), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); 
		modelStack.Translate( 0.284f * windowWidth, 0.25f * windowHeight, 1);
		modelStack.Scale(384, 33, 1);
		Render2DMesh(model->getLv2(), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); 
		modelStack.Translate( 0.284f * windowWidth, 0.2f * windowHeight, 1);
		modelStack.Scale(384, 33, 1);
		Render2DMesh(model->getLv3(), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); 
		modelStack.Translate( 0.284f * windowWidth, 0.15f * windowHeight, 1);
		modelStack.Scale(384, 33, 1);
		Render2DMesh(model->getLv4(), false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		MenuModel* model = dynamic_cast<MenuModel *>(m_model);
		int windowWidth, windowHeight;
		glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
		std::ostringstream ss;
		ss << getHighScore();
		RenderTextOnScreen(model->getTextMesh(), ss.str(), Color(1, 1, 1), 60, windowWidth * 0.65, windowHeight * 0.3);
		modelStack.PopMatrix();
	}
}

string MenuView::getHighScore()
{

	string line;
	std::ifstream HighScorefile("HighScore.txt");
	if (HighScorefile.is_open())
	{
		while (std::getline(HighScorefile, line))
		{
			return line;
		}
		HighScorefile.close();
	}
	else std::cout << "cannot open file";
}