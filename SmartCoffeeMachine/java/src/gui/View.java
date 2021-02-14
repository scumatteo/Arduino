package gui;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.shape.Rectangle;
import javafx.stage.Screen;
import javafx.stage.Stage;
import message.MessageManager;

public class View{
	
	private Group root = new Group();
	private Scene scene = new Scene(root, Screen.getPrimary().getBounds().getWidth()/2, Screen.getPrimary().getBounds().getHeight()/2);
	private Stage stage;
	private List<Rectangle> sugar = new ArrayList<>();
	private int level;
	private Label sugarLabel = new Label("Sugar level");
	private Button button = new Button("Refill coffee");
	private ObservableList<String> coffeeList = FXCollections.observableArrayList("5", "10", "20");
	private ComboBox<String> menu = new ComboBox<>();
	private MessageManager m;
	private TextArea text = new TextArea();
	private String msg;
	
	
	public View(Stage stage) {
		this.menu.setItems(coffeeList);
		this.stage = stage;
		this.stage.setScene(scene);
		this.root.getChildren().add(sugarLabel);
		this.root.getChildren().add(button);
		this.button.setDisable(true);
		this.menu.setDisable(true);
		this.menu.getSelectionModel().selectFirst();
		this.root.getChildren().add(menu);
		this.text.setEditable(false);
		this.root.getChildren().add(text);
		this.stage.setMinWidth(400);
		this.stage.setMinHeight(300);
		this.stage.show();
	}
	
	public void init(MessageManager m) {
		this.m = m;
	}
	
	public void setSugar(int level) {
		this.level = level;
	}
	
	private void drawSugar() {
		this.root.getChildren().removeAll(sugar);
		this.sugar.clear();
		this.sugar = IntStream.range(0, level).mapToObj(x -> new Rectangle(100, 40)).collect(Collectors.toList());
		this.sugar.forEach(r -> r.setX(20));
		for(int i = 0; i < this.sugar.size(); i++) {
			this.sugar.get(i).setY(250-((this.sugar.size()-i)*50));
		}
		this.root.getChildren().addAll(sugar);
	}	
	
	public void setMaintenanceOn() {
		this.button.setDisable(false);
		this.menu.setDisable(false);
	}
	
	public void setMessage(String msg) {
		this.msg = msg;
	}
	
	private void printMessage() {
		this.text.clear();
		this.text.setText(msg);
	}
	
	public void controllerButton() {
		this.button.setOnMouseClicked(e -> {
			this.m.sendMassage(this.menu.getSelectionModel().getSelectedItem());
			this.button.setDisable(true);
			this.menu.setDisable(true);
		});
	}
	
	public void updateView() {
		this.printMessage();
		this.drawSugar();
		this.drawComponent();
		this.controllerButton();
	}
	
	private double screenX() {
		return this.scene.getWidth();
	}
	
	private double screenY() {
		return this.scene.getHeight();
	}
	
	private void drawComponent() {
		this.sugarLabel.setLayoutX(this.screenX()/30);
		this.sugarLabel.setLayoutY(this.screenY()/30);
		this.button.setLayoutX(this.screenX()/3);
		this.button.setLayoutY(this.screenY()/30);
		this.menu.setLayoutX(this.screenX()/3);
		this.menu.setLayoutY(this.button.getHeight()+this.button.getLayoutY());
		this.text.setLayoutX(this.screenX()/3);
		this.text.setLayoutY(this.screenY()/2);
		this.text.setMaxWidth(this.screenX()/2);
		this.text.setMaxHeight(this.screenY()/8);
	}
	
	
}
	
