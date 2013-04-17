package com.badlogic.androidgames.mrnom;

import java.util.List;

import com.badlogic.androidgames.framework.Graphics;
import com.badlogic.androidgames.framework.Input.TouchEvent;
import com.badlogic.androidgames.framework.impl.GameContext;
import com.badlogic.androidgames.framework.impl.GameScreen;

public class MainMenuScreen extends GameScreen {

	public MainMenuScreen(GameContext context) {
		super(context);
	}

	@Override
	public void update(float deltaTime) {
		Graphics g = context.getGraphics();
		List<TouchEvent> touchEvents = context.getInput().getTouchEvents();
		context.getInput().getKeyEvents();

		int len = touchEvents.size();
		for (int i = 0; i < len; i++) {
			TouchEvent event = touchEvents.get(i);
			if (event.type == TouchEvent.TOUCH_UP) {
				if (inBounds(event, 0, g.getHeight() - 64, 64, 64)) {
					Settings.soundEnabled = !Settings.soundEnabled;
					if (Settings.soundEnabled)
						Assets.click.play(1);
				}
				if (inBounds(event, 64, 220, 192, 42)) {
					context.setScreen(new LevelScreen(context));
					if (Settings.soundEnabled)
						Assets.click.play(1);
					return;
				}
				if (inBounds(event, 64, 220 + 42, 192, 42)) {
					context.setScreen(new HighscoreScreen(context));
					if (Settings.soundEnabled)
						Assets.click.play(1);
					return;
				}
				if (inBounds(event, 64, 220 + 84, 192, 42)) {
					context.setScreen(new HelpScreen(context));
					if (Settings.soundEnabled)
						Assets.click.play(1);
					return;
				}
			}
		}
	}

	private boolean inBounds(TouchEvent event, int x, int y, int width, int height) {
		if (event.x > x && event.x < x + width - 1 && event.y > y && event.y < y + height - 1)
			return true;
		else
			return false;
	}

	@Override
	public void render(float deltaTime) {
		Graphics g = context.getGraphics();

		g.drawPixmap(Assets.background, 0, 0);
		g.drawPixmap(Assets.logo, 32, 20);
		g.drawPixmap(Assets.mainMenu, 64, 220);
		if (Settings.soundEnabled)
			g.drawPixmap(Assets.buttons, 0, 416, 0, 0, 64, 64);
		else
			g.drawPixmap(Assets.buttons, 0, 416, 64, 0, 64, 64);
	}

	@Override
	public void pause() {
		Settings.save(context.getFileIO());
	}

	@Override
	public void resume() {
	}

	@Override
	public void dispose() {
	}
}
