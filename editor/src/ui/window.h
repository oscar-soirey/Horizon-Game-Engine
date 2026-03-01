#ifndef AH2D_IMGUI_WINDOW
#define AH2D_IMGUI_WINDOW

namespace editor
{
	class Window {
	public:
		bool visible = false;

		Window()=default;
		virtual ~Window()=default;

		void Show(double _dt);
		void SetTitle(const char* _title);

	protected:
		virtual void Logic(double _dt) {}
		virtual void content();
		virtual void ResizeCallback(int _width, int _height) {}
		const char* title="";

	private:
		float width_=0.f;
		float height_=0.f;
	};
}

#endif