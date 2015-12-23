#include "AppDelegate.h"
#include "Egipt.h"

USING_NS_CC;

Scene* Egipt::createScene()
{
	auto scene = Scene::createWithPhysics();

	auto layer = Egipt::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

bool Egipt::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setScale(0.7);

	//INITIALIZE ATRIBUTES

	visibleSize = Director::getInstance()->getVisibleSize();

	moveRight = false;
	moveLeft = false;
	moveCam = false;
	key = ' ';
	AKeyCounter = 0;
	contactBody = PhysicsBody::create();
	contactFloor = NULL;
	contactEnemy = PhysicsBody::create();

	//CREATE PARALLAX NODE

	backgroundNode = CCParallaxNode::create();
	addChild(backgroundNode, -1);

	//CREATE BACKGROUND LAYERS

	createBackground();

	//CREATE POWER UPS

	power1 = new PowerUps(1);
	addChild(power1->flyParticle, 5);
	addChild(power1->flyParticleSmoke, 5);

	power2 = new PowerUps(2);
	addChild(power2->shadowParticle, 6);

	//CREATE FLOOR LAYERS

	Layer51 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo1.png");
	Layer51->setPosition(Point(Layer51->getContentSize().width / 2 - 2000, Layer51->getContentSize().height / 2 - 1670));

	addChild(Layer51, 5);

	Layer52 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo2.png");
	Layer52->setPosition(Point(Layer52->getContentSize().width / 2 + 14168 - 2000, Layer52->getContentSize().height / 2 - 1675));

	addChild(Layer52, 5);

	Layer53 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo3.png");
	Layer53->setPosition(Point(Layer53->getContentSize().width / 2 + 14177 + 14168 - 2000, Layer53->getContentSize().height / 2 - 1670));

	addChild(Layer53, 5);

	Layer54 = Sprite::create("images/Egipt/Layers/Egipt_Layer5_Modulo4.png");
	Layer54->setPosition(Point(Layer54->getContentSize().width / 2 + 14177 + 14177 + 14162 - 2000, Layer54->getContentSize().height / 2 - 1670));

	addChild(Layer54, 5);

	Layer72 = Sprite::create("images/Egipt/Layers/Egipt_Layer7_Modulo2.png");
	Layer72->setPosition(Point(Layer72->getContentSize().width / 2 + 14168 - 2000, Layer72->getContentSize().height / 2 - 1675));

	addChild(Layer72, 6);

	Layer73 = Sprite::create("images/Egipt/Layers/Egipt_Layer7_Modulo3.png");
	Layer73->setPosition(Point(Layer73->getContentSize().width / 2 + 14177 + 14168 - 2000, Layer73->getContentSize().height / 2 - 1670));

	addChild(Layer73, 6);

	//CREATE FLOOR LAYERS

	//FLOOR COLLIDERS

	Floor1 = Sprite::create();
	Floor1->setPosition(Point(2078, 70));
	Floor1->setVisible(false);

	addChild(Floor1, 5);

	FloorCollider1 = PhysicsBody::createBox(Size(3988, 80));
	FloorCollider1->setContactTestBitmask(true);
	FloorCollider1->setDynamic(true);
	FloorCollider1->setCollisionBitmask(0);
	FloorCollider1->setGravityEnable(false);
	FloorCollider1->setTag(-1);

	Floor1->setPhysicsBody(FloorCollider1);

	////////////////////////////////////

	Floor2 = Sprite::create();
	Floor2->setPosition(Point(6885, -220));
	Floor2->setVisible(false);

	addChild(Floor2, 5);

	FloorCollider2 = PhysicsBody::createBox(Size(5620, 80));
	FloorCollider2->setContactTestBitmask(true);
	FloorCollider2->setDynamic(true);
	FloorCollider2->setCollisionBitmask(0);
	FloorCollider2->setGravityEnable(false);
	FloorCollider2->setTag(-1);

	Floor2->setPhysicsBody(FloorCollider2);

	////////////////////////////////////

	Floor3 = Sprite::create();
	Floor3->setPosition(Point(28312, 70));
	Floor3->setVisible(false);

	addChild(Floor3, 5);

	FloorCollider3 = PhysicsBody::createBox(Size(37225, 80));
	FloorCollider3->setContactTestBitmask(true);
	FloorCollider3->setDynamic(true);
	FloorCollider3->setCollisionBitmask(0);
	FloorCollider3->setGravityEnable(false);
	FloorCollider3->setTag(-1);

	Floor3->setPhysicsBody(FloorCollider3);

	////////////////////////////////////

	Floor1Modulo1 = Sprite::create();
	Floor1Modulo1->setPosition(Point(4823, 60));
	Floor1Modulo1->setVisible(true);

	addChild(Floor1Modulo1, 5);

	FloorCollider1Modulo1 = PhysicsBody::createBox(Size(690, 80));
	FloorCollider1Modulo1->setContactTestBitmask(true);
	FloorCollider1Modulo1->setDynamic(true);
	FloorCollider1Modulo1->setCollisionBitmask(0);
	FloorCollider1Modulo1->setGravityEnable(false);
	FloorCollider1Modulo1->setTag(-1);

	Floor1Modulo1->setPhysicsBody(FloorCollider1Modulo1);

	//////////////////////////////////

	Floor2Modulo1 = Sprite::create();
	Floor2Modulo1->setPosition(Point(8742, 60));
	Floor2Modulo1->setVisible(true);

	addChild(Floor2Modulo1, 5);

	FloorCollider2Modulo1 = PhysicsBody::createBox(Size(690, 80));
	FloorCollider2Modulo1->setContactTestBitmask(true);
	FloorCollider2Modulo1->setDynamic(true);
	FloorCollider2Modulo1->setCollisionBitmask(0);
	FloorCollider2Modulo1->setGravityEnable(false);
	FloorCollider2Modulo1->setTag(-1);

	Floor2Modulo1->setPhysicsBody(FloorCollider2Modulo1);

	//////////////////////////////////

	Floor1Modulo2 = Sprite::create();
	Floor1Modulo2->setPosition(Point(12802, 769));
	Floor1Modulo2->setVisible(true);

	addChild(Floor1Modulo2, 5);

	FloorCollider1Modulo2 = PhysicsBody::createBox(Size(1080, 80));
	FloorCollider1Modulo2->setContactTestBitmask(true);
	FloorCollider1Modulo2->setDynamic(true);
	FloorCollider1Modulo2->setCollisionBitmask(0);
	FloorCollider1Modulo2->setGravityEnable(false);
	FloorCollider1Modulo2->setTag(-1);

	Floor1Modulo2->setPhysicsBody(FloorCollider1Modulo2);

	//////////////////////////////////

	Floor2Modulo2 = Sprite::create();
	Floor2Modulo2->setPosition(Point(15828, 769));
	Floor2Modulo2->setVisible(true);

	addChild(Floor2Modulo2, 5);

	FloorCollider2Modulo2 = PhysicsBody::createBox(Size(1860, 80));
	FloorCollider2Modulo2->setContactTestBitmask(true);
	FloorCollider2Modulo2->setDynamic(true);
	FloorCollider2Modulo2->setCollisionBitmask(0);
	FloorCollider2Modulo2->setGravityEnable(false);
	FloorCollider2Modulo2->setTag(-1);

	Floor2Modulo2->setPhysicsBody(FloorCollider2Modulo2);

	//////////////////////////////////

	Floor3Modulo2 = Sprite::create();
	Floor3Modulo2->setPosition(Point(16552, 1142));
	Floor3Modulo2->setVisible(true);

	addChild(Floor3Modulo2, 5);

	FloorCollider3Modulo2 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider3Modulo2->setContactTestBitmask(true);
	FloorCollider3Modulo2->setDynamic(true);
	FloorCollider3Modulo2->setCollisionBitmask(0);
	FloorCollider3Modulo2->setGravityEnable(false);
	FloorCollider3Modulo2->setTag(-1);

	Floor3Modulo2->setPhysicsBody(FloorCollider3Modulo2);

	//////////////////////////////////

	Floor4Modulo2 = Sprite::create();
	Floor4Modulo2->setPosition(Point(17177, 1289));
	Floor4Modulo2->setVisible(true);

	addChild(Floor4Modulo2, 5);

	FloorCollider4Modulo2 = PhysicsBody::createBox(Size(570, 80));
	FloorCollider4Modulo2->setContactTestBitmask(true);
	FloorCollider4Modulo2->setDynamic(true);
	FloorCollider4Modulo2->setCollisionBitmask(0);
	FloorCollider4Modulo2->setGravityEnable(false);
	FloorCollider4Modulo2->setTag(-1);

	Floor4Modulo2->setPhysicsBody(FloorCollider4Modulo2);

	//////////////////////////////////

	Floor5Modulo2 = Sprite::create();
	Floor5Modulo2->setPosition(Point(14294, 440));
	Floor5Modulo2->setVisible(true);

	addChild(Floor5Modulo2, 5);

	FloorCollider5Modulo2 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider5Modulo2->setContactTestBitmask(true);
	FloorCollider5Modulo2->setDynamic(true);
	FloorCollider5Modulo2->setCollisionBitmask(0);
	FloorCollider5Modulo2->setGravityEnable(false);
	FloorCollider5Modulo2->setTag(-1);

	Floor5Modulo2->setPhysicsBody(FloorCollider5Modulo2);

	//////////////////////////////////

	Floor6Modulo2 = Sprite::create();
	Floor6Modulo2->setPosition(Point(21294, 769));
	Floor6Modulo2->setVisible(true);

	addChild(Floor6Modulo2, 5);

	FloorCollider6Modulo2 = PhysicsBody::createBox(Size(1400, 80));
	FloorCollider6Modulo2->setContactTestBitmask(true);
	FloorCollider6Modulo2->setDynamic(true);
	FloorCollider6Modulo2->setCollisionBitmask(0);
	FloorCollider6Modulo2->setGravityEnable(false);
	FloorCollider6Modulo2->setTag(-1);

	Floor6Modulo2->setPhysicsBody(FloorCollider6Modulo2);

	//////////////////////////////////

	Floor7Modulo2 = Sprite::create();
	Floor7Modulo2->setPosition(Point(21171, 1142));
	Floor7Modulo2->setVisible(true);

	addChild(Floor7Modulo2, 5);

	FloorCollider7Modulo2 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider7Modulo2->setContactTestBitmask(true);
	FloorCollider7Modulo2->setDynamic(true);
	FloorCollider7Modulo2->setCollisionBitmask(0);
	FloorCollider7Modulo2->setGravityEnable(false);
	FloorCollider7Modulo2->setTag(-1);

	Floor7Modulo2->setPhysicsBody(FloorCollider7Modulo2);

	//////////////////////////////////

	Floor8Modulo2 = Sprite::create();
	Floor8Modulo2->setPosition(Point(21717, 1265));
	Floor8Modulo2->setVisible(true);

	addChild(Floor8Modulo2, 5);

	FloorCollider8Modulo2 = PhysicsBody::createBox(Size(570, 80));
	FloorCollider8Modulo2->setContactTestBitmask(true);
	FloorCollider8Modulo2->setDynamic(true);
	FloorCollider8Modulo2->setCollisionBitmask(0);
	FloorCollider8Modulo2->setGravityEnable(false);
	FloorCollider8Modulo2->setTag(-1);

	Floor8Modulo2->setPhysicsBody(FloorCollider8Modulo2);

	//////////////////////////////////

	Floor9Modulo2 = Sprite::create();
	Floor9Modulo2->setPosition(Point(22585, 1570));
	Floor9Modulo2->setVisible(true);

	addChild(Floor9Modulo2, 5);

	FloorCollider9Modulo2 = PhysicsBody::createBox(Size(180, 80));
	FloorCollider9Modulo2->setContactTestBitmask(true);
	FloorCollider9Modulo2->setDynamic(true);
	FloorCollider9Modulo2->setCollisionBitmask(0);
	FloorCollider9Modulo2->setGravityEnable(false);
	FloorCollider9Modulo2->setTag(-1);

	Floor9Modulo2->setPhysicsBody(FloorCollider9Modulo2);

	//////////////////////////////////

	Floor10Modulo2 = Sprite::create();
	Floor10Modulo2->setPosition(Point(23516, 440));
	Floor10Modulo2->setVisible(true);

	addChild(Floor10Modulo2, 5);

	FloorCollider10Modulo2 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider10Modulo2->setContactTestBitmask(true);
	FloorCollider10Modulo2->setDynamic(true);
	FloorCollider10Modulo2->setCollisionBitmask(0);
	FloorCollider10Modulo2->setGravityEnable(false);
	FloorCollider10Modulo2->setTag(-1);

	Floor10Modulo2->setPhysicsBody(FloorCollider10Modulo2);

	//////////////////////////////////

	Floor11Modulo2 = Sprite::create();
	Floor11Modulo2->setPosition(Point(24586, 440));
	Floor11Modulo2->setVisible(true);

	addChild(Floor11Modulo2, 5);

	FloorCollider11Modulo2 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider11Modulo2->setContactTestBitmask(true);
	FloorCollider11Modulo2->setDynamic(true);
	FloorCollider11Modulo2->setCollisionBitmask(0);
	FloorCollider11Modulo2->setGravityEnable(false);
	FloorCollider11Modulo2->setTag(-1);

	Floor11Modulo2->setPhysicsBody(FloorCollider11Modulo2);

	//////////////////////////////////

	Floor12Modulo2 = Sprite::create();
	Floor12Modulo2->setPosition(Point(25706, 440));
	Floor12Modulo2->setVisible(true);

	addChild(Floor12Modulo2, 5);

	FloorCollider12Modulo2 = PhysicsBody::createBox(Size(340, 80));
	FloorCollider12Modulo2->setContactTestBitmask(true);
	FloorCollider12Modulo2->setDynamic(true);
	FloorCollider12Modulo2->setCollisionBitmask(0);
	FloorCollider12Modulo2->setGravityEnable(false);
	FloorCollider12Modulo2->setTag(-1);

	Floor12Modulo2->setPhysicsBody(FloorCollider12Modulo2);

	//////////////////////////////////

	Floor13Modulo2 = Sprite::create();
	Floor13Modulo2->setPosition(Point(19030, 1450));
	Floor13Modulo2->setVisible(true);

	addChild(Floor13Modulo2, 5);

	Floor13ColliderModulo2 = PhysicsBody::createBox(Size(1000, 80));
	Floor13ColliderModulo2->setContactTestBitmask(true);
	Floor13ColliderModulo2->setDynamic(true);
	Floor13ColliderModulo2->setCollisionBitmask(0);
	Floor13ColliderModulo2->setGravityEnable(false);
	Floor13ColliderModulo2->setTag(-1);

	Floor13Modulo2->setPhysicsBody(Floor13ColliderModulo2);

	//////////////////////////////////

	Floor1Modulo3 = Sprite::create();
	Floor1Modulo3->setPosition(Point(27073, 1040));
	Floor1Modulo3->setVisible(true);

	addChild(Floor1Modulo3, 5);

	Floor1ColliderModulo3 = PhysicsBody::createBox(Size(725, 80));
	Floor1ColliderModulo3->setContactTestBitmask(true);
	Floor1ColliderModulo3->setDynamic(true);
	Floor1ColliderModulo3->setCollisionBitmask(0);
	Floor1ColliderModulo3->setGravityEnable(false);
	Floor1ColliderModulo3->setTag(-1);

	Floor1Modulo3->setPhysicsBody(Floor1ColliderModulo3);

	//////////////////////////////////

	Floor2Modulo3 = Sprite::create();
	Floor2Modulo3->setPosition(Point(28328, 440));
	Floor2Modulo3->setVisible(true);

	addChild(Floor2Modulo3, 5);

	Floor2ColliderModulo3 = PhysicsBody::createBox(Size(340, 80));
	Floor2ColliderModulo3->setContactTestBitmask(true);
	Floor2ColliderModulo3->setDynamic(true);
	Floor2ColliderModulo3->setCollisionBitmask(0);
	Floor2ColliderModulo3->setGravityEnable(false);
	Floor2ColliderModulo3->setTag(-1);

	Floor2Modulo3->setPhysicsBody(Floor2ColliderModulo3);

	//////////////////////////////////

	Floor3Modulo3 = Sprite::create();
	Floor3Modulo3->setPosition(Point(29731, 771));
	Floor3Modulo3->setVisible(true);

	addChild(Floor3Modulo3, 5);

	Floor3ColliderModulo3 = PhysicsBody::createBox(Size(1350, 80));
	Floor3ColliderModulo3->setContactTestBitmask(true);
	Floor3ColliderModulo3->setDynamic(true);
	Floor3ColliderModulo3->setCollisionBitmask(0);
	Floor3ColliderModulo3->setGravityEnable(false);
	Floor3ColliderModulo3->setTag(-1);

	Floor3Modulo3->setPhysicsBody(Floor3ColliderModulo3);

	//////////////////////////////////

	Floor4Modulo3 = Sprite::create();
	Floor4Modulo3->setPosition(Point(30138, 1211));
	Floor4Modulo3->setVisible(true);

	addChild(Floor4Modulo3, 5);

	Floor4ColliderModulo3 = PhysicsBody::createBox(Size(340, 80));
	Floor4ColliderModulo3->setContactTestBitmask(true);
	Floor4ColliderModulo3->setDynamic(true);
	Floor4ColliderModulo3->setCollisionBitmask(0);
	Floor4ColliderModulo3->setGravityEnable(false);
	Floor4ColliderModulo3->setTag(-1);

	Floor4Modulo3->setPhysicsBody(Floor4ColliderModulo3);

	//////////////////////////////////

	Floor5Modulo3 = Sprite::create();
	Floor5Modulo3->setPosition(Point(31601, 775));
	Floor5Modulo3->setVisible(true);

	addChild(Floor5Modulo3, 5);

	Floor5ColliderModulo3 = PhysicsBody::createBox(Size(1100, 80));
	Floor5ColliderModulo3->setContactTestBitmask(true);
	Floor5ColliderModulo3->setDynamic(true);
	Floor5ColliderModulo3->setCollisionBitmask(0);
	Floor5ColliderModulo3->setGravityEnable(false);
	Floor5ColliderModulo3->setTag(-1);

	Floor5Modulo3->setPhysicsBody(Floor5ColliderModulo3);

	//////////////////////////////////

	Floor6Modulo3 = Sprite::create();
	Floor6Modulo3->setPosition(Point(31583, 1290));
	Floor6Modulo3->setVisible(true);

	addChild(Floor6Modulo3, 5);

	Floor6ColliderModulo3 = PhysicsBody::createBox(Size(570, 80));
	Floor6ColliderModulo3->setContactTestBitmask(true);
	Floor6ColliderModulo3->setDynamic(true);
	Floor6ColliderModulo3->setCollisionBitmask(0);
	Floor6ColliderModulo3->setGravityEnable(false);
	Floor6ColliderModulo3->setTag(-1);

	Floor6Modulo3->setPhysicsBody(Floor6ColliderModulo3);

	//////////////////////////////////

	Floor7Modulo3 = Sprite::create();
	Floor7Modulo3->setPosition(Point(34098, 771));
	Floor7Modulo3->setVisible(true);

	addChild(Floor7Modulo3, 5);

	Floor7ColliderModulo3 = PhysicsBody::createBox(Size(1400, 80));
	Floor7ColliderModulo3->setContactTestBitmask(true);
	Floor7ColliderModulo3->setDynamic(true);
	Floor7ColliderModulo3->setCollisionBitmask(0);
	Floor7ColliderModulo3->setGravityEnable(false);
	Floor7ColliderModulo3->setTag(-1);

	Floor7Modulo3->setPhysicsBody(Floor7ColliderModulo3);

	//////////////////////////////////

	Floor8Modulo3 = Sprite::create();
	Floor8Modulo3->setPosition(Point(33974, 1211));
	Floor8Modulo3->setVisible(true);

	addChild(Floor8Modulo3, 5);

	Floor8ColliderModulo3 = PhysicsBody::createBox(Size(340, 80));
	Floor8ColliderModulo3->setContactTestBitmask(true);
	Floor8ColliderModulo3->setDynamic(true);
	Floor8ColliderModulo3->setCollisionBitmask(0);
	Floor8ColliderModulo3->setGravityEnable(false);
	Floor8ColliderModulo3->setTag(-1);

	Floor8Modulo3->setPhysicsBody(Floor8ColliderModulo3);

	//////////////////////////////////

	Floor9Modulo3 = Sprite::create();
	Floor9Modulo3->setPosition(Point(34528, 1275));
	Floor9Modulo3->setVisible(true);

	addChild(Floor9Modulo3, 5);

	Floor9ColliderModulo3 = PhysicsBody::createBox(Size(565, 80));
	Floor9ColliderModulo3->setContactTestBitmask(true);
	Floor9ColliderModulo3->setDynamic(true);
	Floor9ColliderModulo3->setCollisionBitmask(0);
	Floor9ColliderModulo3->setGravityEnable(false);
	Floor9ColliderModulo3->setTag(-1);

	Floor9Modulo3->setPhysicsBody(Floor9ColliderModulo3);

	//////////////////////////////////

	Floor10Modulo3 = Sprite::create();
	Floor10Modulo3->setPosition(Point(35413, 440));
	Floor10Modulo3->setVisible(true);

	addChild(Floor10Modulo3, 5);

	Floor10ColliderModulo3 = PhysicsBody::createBox(Size(340, 80));
	Floor10ColliderModulo3->setContactTestBitmask(true);
	Floor10ColliderModulo3->setDynamic(true);
	Floor10ColliderModulo3->setCollisionBitmask(0);
	Floor10ColliderModulo3->setGravityEnable(false);
	Floor10ColliderModulo3->setTag(-1);

	Floor10Modulo3->setPhysicsBody(Floor10ColliderModulo3);

	//////////////////////////////////

	Floor11Modulo3 = Sprite::create();
	Floor11Modulo3->setPosition(Point(37076, 668));
	Floor11Modulo3->setVisible(true);

	addChild(Floor11Modulo3, 5);

	Floor11ColliderModulo3 = PhysicsBody::createBox(Size(1315, 80));
	Floor11ColliderModulo3->setContactTestBitmask(true);
	Floor11ColliderModulo3->setDynamic(true);
	Floor11ColliderModulo3->setCollisionBitmask(0);
	Floor11ColliderModulo3->setGravityEnable(false);
	Floor11ColliderModulo3->setTag(-1);

	Floor11Modulo3->setPhysicsBody(Floor11ColliderModulo3);

	//////////////////////////////////

	Floor12Modulo3 = Sprite::create();
	Floor12Modulo3->setPosition(Point(37028, 1520));
	Floor12Modulo3->setVisible(true);

	addChild(Floor12Modulo3, 5);

	Floor12ColliderModulo3 = PhysicsBody::createBox(Size(1090, 80));
	Floor12ColliderModulo3->setContactTestBitmask(true);
	Floor12ColliderModulo3->setDynamic(true);
	Floor12ColliderModulo3->setCollisionBitmask(0);
	Floor12ColliderModulo3->setGravityEnable(false);
	Floor12ColliderModulo3->setTag(-1);

	Floor12Modulo3->setPhysicsBody(Floor12ColliderModulo3);

	//////////////////////////////////

	Floor13Modulo3 = Sprite::create();
	Floor13Modulo3->setPosition(Point(39104, 440));
	Floor13Modulo3->setVisible(true);

	addChild(Floor13Modulo3, 5);

	Floor13ColliderModulo3 = PhysicsBody::createBox(Size(340, 80));
	Floor13ColliderModulo3->setContactTestBitmask(true);
	Floor13ColliderModulo3->setDynamic(true);
	Floor13ColliderModulo3->setCollisionBitmask(0);
	Floor13ColliderModulo3->setGravityEnable(false);
	Floor13ColliderModulo3->setTag(-1);

	Floor13Modulo3->setPhysicsBody(Floor13ColliderModulo3);

	//////////////////////////////////

	Floor1Modulo4 = Sprite::create();
	Floor1Modulo4->setPosition(Point(51712, 300));
	Floor1Modulo4->setVisible(true);

	addChild(Floor1Modulo4, 5);

	Floor1ColliderModulo4 = PhysicsBody::createBox(Size(5970, 80));
	Floor1ColliderModulo4->setContactTestBitmask(true);
	Floor1ColliderModulo4->setDynamic(true);
	Floor1ColliderModulo4->setCollisionBitmask(0);
	Floor1ColliderModulo4->setGravityEnable(false);
	Floor1ColliderModulo4->setTag(-1);

	Floor1Modulo4->setPhysicsBody(Floor1ColliderModulo4);

	//FLOOR COLLIDERS

	//WALL COLLIDERS

	Wall0 = Sprite::create("images/Egipt/Colliders/Wall0Collider.png");
	Wall0->setPosition(Point((Wall0->getContentSize().width / 2) - 300, (Wall0->getContentSize().height / 2)));
	Wall0->setVisible(false);

	addChild(Wall0, 5);

	Wall0Collider = PhysicsBody::createBox(Size(Wall0->getContentSize().width, Wall0->getContentSize().height));
	Wall0Collider->setContactTestBitmask(true);
	Wall0Collider->setDynamic(true);
	Wall0Collider->setCollisionBitmask(0);
	Wall0Collider->setGravityEnable(false);
	Wall0Collider->setTag(-2);

	Wall0->setPhysicsBody(Wall0Collider);

	//////////////////////////////////

	Wall1 = Sprite::create();
	Wall1->setPosition(Point(4698, -103));
	Wall1->setVisible(false);

	addChild(Wall1, 5);

	Wall1Collider = PhysicsBody::createBox(Size(80, 234));
	Wall1Collider->setContactTestBitmask(true);
	Wall1Collider->setDynamic(true);
	Wall1Collider->setCollisionBitmask(0);
	Wall1Collider->setGravityEnable(false);
	Wall1Collider->setTag(-2);

	Wall1->setPhysicsBody(Wall1Collider);

	//////////////////////////////////

	Wall2 = Sprite::create();
	Wall2->setPosition(Point(8934, -103));
	Wall2->setVisible(false);

	addChild(Wall2, 5);

	Wall2Collider = PhysicsBody::createBox(Size(80, 234));
	Wall2Collider->setContactTestBitmask(true);
	Wall2Collider->setDynamic(true);
	Wall2Collider->setCollisionBitmask(0);
	Wall2Collider->setGravityEnable(false);
	Wall2Collider->setTag(-2);

	Wall2->setPhysicsBody(Wall2Collider);

	//////////////////////////////////

	Wall3 = Sprite::create();
	Wall3->setPosition(Point(48925, 1000));
	Wall3->setVisible(false);

	addChild(Wall3, 5);

	Wall3Collider = PhysicsBody::createBox(Size(80, 5000));
	Wall3Collider->setContactTestBitmask(true);
	Wall3Collider->setDynamic(true);
	Wall3Collider->setCollisionBitmask(0);
	Wall3Collider->setGravityEnable(false);
	Wall3Collider->setTag(-2);

	Wall3->setPhysicsBody(Wall3Collider);

	//////////////////////////////////

	Wall2Modulo2 = Sprite::create();
	Wall2Modulo2->setPosition(Point(16892, 1000));
	Wall2Modulo2->setVisible(true);

	addChild(Wall2Modulo2, 5);

	Wall2ColliderModulo2 = PhysicsBody::createBox(Size(80, 230));
	Wall2ColliderModulo2->setContactTestBitmask(true);
	Wall2ColliderModulo2->setDynamic(true);
	Wall2ColliderModulo2->setCollisionBitmask(0);
	Wall2ColliderModulo2->setGravityEnable(false);
	Wall2ColliderModulo2->setTag(-2);

	Wall2Modulo2->setPhysicsBody(Wall2ColliderModulo2);

	//////////////////////////////////

	Wall3Modulo2 = Sprite::create();
	Wall3Modulo2->setPosition(Point(22574.5, 833));
	Wall3Modulo2->setVisible(true);

	addChild(Wall3Modulo2, 5);

	Wall3ColliderModulo2 = PhysicsBody::createBox(Size(660, 1160));
	Wall3ColliderModulo2->setContactTestBitmask(true);
	Wall3ColliderModulo2->setDynamic(true);
	Wall3ColliderModulo2->setCollisionBitmask(0);
	Wall3ColliderModulo2->setGravityEnable(false);
	Wall3ColliderModulo2->setTag(-2);

	Wall3Modulo2->setPhysicsBody(Wall3ColliderModulo2);

	//////////////////////////////////

	Wall1Modulo4 = Sprite::create();
	Wall1Modulo4->setPosition(Point(48765, 173));
	Wall1Modulo4->setVisible(true);

	addChild(Wall1Modulo4, 5);

	Wall1ColliderModulo4 = PhysicsBody::createBox(Size(80, 140));
	Wall1ColliderModulo4->setContactTestBitmask(true);
	Wall1ColliderModulo4->setDynamic(true);
	Wall1ColliderModulo4->setCollisionBitmask(0);
	Wall1ColliderModulo4->setGravityEnable(false);
	Wall1ColliderModulo4->setTag(-2);

	Wall1Modulo4->setPhysicsBody(Wall1ColliderModulo4);

	//CREATE INTERACTIVE ITEMS

	//VASIJAS

	vasijaPequena1 = new Item(2, 15727, 60);
	objectsVector.pushBack(vasijaPequena1);
	tag = (vasijaPequena1->itemType * 1000) + objectsVector.getIndex(vasijaPequena1);
	vasijaPequena1->itemCollider->setTag(tag);
	addChild(vasijaPequena1->itemArt, 5);
	tag += 100;
	vasijaPequena1->itemSoundCollider->setTag(tag);
	addChild(vasijaPequena1->itemSound, 5);

	vasijaPequena2 = new Item(2, 16127, 60);
	objectsVector.pushBack(vasijaPequena2);
	tag = (vasijaPequena2->itemType * 1000) + objectsVector.getIndex(vasijaPequena2);
	vasijaPequena2->itemCollider->setTag(tag);
	addChild(vasijaPequena2->itemArt, 5);
	tag += 100;
	vasijaPequena2->itemSoundCollider->setTag(tag);
	addChild(vasijaPequena2->itemSound, 5);

	vasijaPequena3 = new Item(2, 20807, 60);
	objectsVector.pushBack(vasijaPequena3);
	tag = (vasijaPequena3->itemType * 1000) + objectsVector.getIndex(vasijaPequena3);
	vasijaPequena3->itemCollider->setTag(tag);
	addChild(vasijaPequena3->itemArt, 5);
	tag += 100;
	vasijaPequena3->itemSoundCollider->setTag(tag);
	addChild(vasijaPequena3->itemSound, 5);

	vasijaPequena4 = new Item(2, 16942, 1285);
	objectsVector.pushBack(vasijaPequena4);
	tag = (vasijaPequena4->itemType * 1000) + objectsVector.getIndex(vasijaPequena4);
	vasijaPequena4->itemCollider->setTag(tag);
	addChild(vasijaPequena4->itemArt, 5);
	tag += 100;
	vasijaPequena4->itemSoundCollider->setTag(tag);
	addChild(vasijaPequena4->itemSound, 5);

	vasijaPequena5 = new Item(2, 19078, 1468);
	objectsVector.pushBack(vasijaPequena5);
	tag = (vasijaPequena5->itemType * 1000) + objectsVector.getIndex(vasijaPequena5);
	vasijaPequena5->itemCollider->setTag(tag);
	addChild(vasijaPequena5->itemArt, 5);
	tag += 100;
	vasijaPequena5->itemSoundCollider->setTag(tag);
	addChild(vasijaPequena5->itemSound, 5);

	vasijaPequena6 = new Item(2, 20622, 814);
	objectsVector.pushBack(vasijaPequena6);
	tag = (vasijaPequena6->itemType * 1000) + objectsVector.getIndex(vasijaPequena6);
	vasijaPequena6->itemCollider->setTag(tag);
	addChild(vasijaPequena6->itemArt, 5);
	tag += 100;
	vasijaPequena6->itemSoundCollider->setTag(tag);
	addChild(vasijaPequena6->itemSound, 5);

	//VASIJAS GRANDES

	vasijaGrande1 = new Item(3, 18915, 60);
	objectsVector.pushBack(vasijaGrande1);
	tag = (vasijaGrande1->itemType * 1000) + objectsVector.getIndex(vasijaGrande1);
	vasijaGrande1->itemCollider->setTag(tag);
	addChild(vasijaGrande1->itemArt, 5);

	vasijaGrande2 = new Item(3, 21813, 60);
	objectsVector.pushBack(vasijaGrande2);
	tag = (vasijaGrande2->itemType * 2000) + objectsVector.getIndex(vasijaGrande2);
	vasijaGrande2->itemCollider->setTag(tag);
	addChild(vasijaGrande2->itemArt, 5);

	//CREATE INTERACTIVE ITEMS

	//CREATE ANIMATED OBJECTS

	createAnimations();

	//CREATE CHARACTER

	Iniko = new Character(1, 0);

	addChild(Iniko->runningSoundColliderSprite, 5);
	addChild(Iniko->characterIdlerightspritebatch, 5);
	addChild(Iniko->characterRunningRightspritebatch, 5);
	addChild(Iniko->characterIdleleftspritebatch, 5);
	addChild(Iniko->characterRunningLeftspritebatch, 5);
	addChild(Iniko->characterJumpingRight, 5);
	addChild(Iniko->characterJumpingLeft, 5);
	addChild(Iniko->characterStealthRightspritebatch, 5);
	addChild(Iniko->characterStealthLeftspritebatch, 5);

	addChild(Iniko->characterVision, 5);
	addChild(Iniko->AKey, 5);
	addChild(Iniko->SKey, 5);
	addChild(Iniko->forceBar, 5);
	addChild(Iniko->forceBarBorder, 5);

	barco1 = Sprite::create("images/Egipt/Assets/barca.png");
	barco1->setPosition(Point(4823, 250));
	addChild(barco1, 5);

	barco2 = Sprite::create("images/Egipt/Assets/barca.png");
	barco2->setPosition(Point(8742, 250));
	addChild(barco2, 5);

	//INITIALIZE UPDATE FUNCTION

	this->scheduleUpdate();

	//CREATE KEY INPUTS LISTENERS

	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Egipt::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Egipt::onKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//CREATE PHYSIC CONTACT LISTENER

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Egipt::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Egipt::onContactSeparate, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void Egipt::createBackground()
{
	/*Layer0->setPosition(Point((Layer0->getContentSize().width / 2) - 3000 + Iniko->characterVision->getPosition().x, (Layer0->getContentSize().height / 2)));
	Layer1->setPosition(Point((Layer1->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.05, (Layer1->getContentSize().height / 2)));
	Layer2->setPosition(Point((Layer2->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.06, (Layer2->getContentSize().height / 2)));
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.07, (Layer3->getContentSize().height / 2)));
	//Layer4->setPosition(Point((Layer4->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.7, (Layer4->getContentSize().height / 2)));*/

	Layer0 = Sprite::create("images/Egipt/Layers/Egipt_Layer.png");
	Layer0->setPosition(Point((Layer0->getContentSize().width / 2) - 3000, (Layer0->getContentSize().height / 2)));
	//Layer0->setTag(80);

	addChild(Layer0, 0);
	//backgroundNode->addChild(Layer0, 0, ccp(0, 0), Point((Layer0->getContentSize().width / 2) - 3000, (Layer0->getContentSize().height / 2) - 100));

	Layer1 = Sprite::create("images/Egipt/Layers/Egipt_Layer1.png");
	Layer1->setPosition(Point((Layer1->getContentSize().width / 2) - 2000, (Layer1->getContentSize().height / 2)));
	//Layer1->setTag(81);

	addChild(Layer1, 1);
	//backgroundNode->addChild(Layer1, 1, ccp(0, 0), Point((Layer1->getContentSize().width / 2) - 2000, (Layer1->getContentSize().height / 2) - 100));

	Layer2 = Sprite::create("images/Egipt/Layers/Egipt_Layer2.png");
	Layer2->setPosition(Point((Layer2->getContentSize().width / 2) - 2000, (Layer2->getContentSize().height / 2)));
	//Layer2->setTag(82);

	addChild(Layer2, 2);
	//backgroundNode->addChild(Layer2, 2, ccp(0, 0), Point((Layer2->getContentSize().width / 2) - 2000, (Layer2->getContentSize().height / 2) - 100));

	Layer3 = Sprite::create("images/Egipt/Layers/Egipt_Layer3.png");
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2) - 2000, (Layer3->getContentSize().height / 2)));
	//Layer3->setTag(83);

	addChild(Layer3, 3);
	//backgroundNode->addChild(Layer3, 3, ccp(0, 0), Point((Layer3->getContentSize().width / 2) - 2000, (Layer3->getContentSize().height / 2) - 100));

	Layer4 = Sprite::create("images/Egipt/Layers/Egipt_Layer4.png");
	Layer4->setPosition(Point((Layer4->getContentSize().width / 2) - 2000, (Layer4->getContentSize().height / 2)));
	//Layer4->setTag(84);

	addChild(Layer4, 4);
	//backgroundNode->addChild(Layer4, 4, ccp(0, 0), Point((Layer4->getContentSize().width / 2) - 2000, (Layer4->getContentSize().height / 2) - 100));

	//ILUMINATION

	Layer61 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo1.png");
	Layer61->setPosition(Point(Layer61->getContentSize().width / 2 - 2000, Layer61->getContentSize().height / 2 - 1668));

	addChild(Layer61, 7);

	Layer62 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo2.png");
	Layer62->setPosition(Point(Layer62->getContentSize().width / 2 + 14171 - 2000, Layer62->getContentSize().height / 2 - 1665));

	addChild(Layer62, 7);

	Layer63 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo3.png");
	Layer63->setPosition(Point(Layer63->getContentSize().width / 2 + 14177 + 14146 - 2000, Layer63->getContentSize().height / 2 - 1665));

	addChild(Layer63, 7);

	Layer64 = Sprite::create("images/Egipt/Layers/Egipt_Layer6_Modulo4.png");
	Layer64->setPosition(Point(Layer64->getContentSize().width / 2 + 14177 + 14177 + 14146 - 2000, Layer64->getContentSize().height / 2 - 1665));

	addChild(Layer64, 7);
}

void Egipt::update(float dt)
{
	deltaTime = dt;

	if (contactFloor == NULL)
	{
		Layer72->setVisible(false);
		Layer73->setVisible(false);
	}

	else
	{
		Layer72->setVisible(true);
		Layer73->setVisible(true);
	}

	//VELOCITY UPDATE

	//if (!Iniko->jumping)
	//{
	Iniko->characterJumpingRightCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterJumpingRightCollider->getVelocity().y));
	Iniko->characterJumpingLeftCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterJumpingLeftCollider->getVelocity().y));
	Iniko->characterIdleRightCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterIdleRightCollider->getVelocity().y));
	Iniko->characterIdleLeftCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterIdleLeftCollider->getVelocity().y));
	Iniko->characterRunningRightCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterRunningRightCollider->getVelocity().y));
	Iniko->characterRunningLeftCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterRunningLeftCollider->getVelocity().y));
	Iniko->characterStealthRightCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterStealthRightCollider->getVelocity().y));
	Iniko->characterStealthLeftCollider->setVelocity(Vec2(500 * Iniko->velocity, Iniko->characterStealthLeftCollider->getVelocity().y));
	//}

	/*else if(Iniko->characterJumpingLeftCollider->getVelocity().y < 0 || Iniko->characterJumpingRightCollider->getVelocity().y < 0)
	{
	Iniko->characterRunningRightCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterRunningRightCollider->getVelocity().y));
	Iniko->characterRunningLeftCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterRunningLeftCollider->getVelocity().y));
	Iniko->characterJumpingRightCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterJumpingRightCollider->getVelocity().y));
	Iniko->characterJumpingLeftCollider->setVelocity(Vec2(250 * Iniko->velocity, Iniko->characterJumpingLeftCollider->getVelocity().y));
	}*/

	//VELOCITY UPDATE

	for (int i = 0; i < objectsVector.size(); i++)
	{
		if (objectsVector.at(i)->itemType == 2)
			objectsVector.at(i)->itemSound->setPosition(objectsVector.at(i)->itemArt->getPosition());
	}

	//EVENTS

	if (Iniko->characterIdleRight->getPositionX() >= 7400 && Iniko->characterIdleRight->getPositionX() <= 7500)
	{
		/*Iniko->runningSoundColliderSprite->setZOrder(5);
		Iniko->characterIdlerightspritebatch->setZOrder(5);
		Iniko->characterRunningRightspritebatch->setZOrder(5);
		Iniko->characterIdleleftspritebatch->setZOrder(5);
		Iniko->characterRunningLeftspritebatch->setZOrder(5);
		Iniko->characterVision->setZOrder(5);
		Iniko->AKey->setZOrder(5);
		Iniko->SKey->setZOrder(5);*/
	}

	/*if (Iniko->characterVision->getPositionX() >= (14381 + 10460) && Iniko->characterVision->getPositionX() <= (14381 + 10685))
	{
	if (key == 'U')
	{
	Iniko->facingRight = false;
	Iniko->characterIdleLeft->setPosition(14381 + 10550, 1386 - Iniko->characterIdleRight->getContentSize().height / 2);
	}
	}*/

	if (Iniko->characterIdleRight->getPositionX() >= 100 && !ready)
	{
		ready = true;

		enemy1 = new Enemy(30188, 30188, 2.0f, 20, 2);
		enemysVector.pushBack(enemy1);
		tag = 1000 + enemysVector.getIndex(enemy1);
		enemy1->enemyCollider->setTag(tag);
		enemy1->facingRight = false;
		enemy1->staticEnemy = true;
		addChild(enemy1->enemyArt, 5);
		addChild(enemy1->enemy2WalkingRightspritebatch, 5);
		addChild(enemy1->enemy2WalkingLeftspritebatch, 5);
		addChild(enemy1->enemy2RunningRightspritebatch, 5);
		addChild(enemy1->enemy2RunningLeftspritebatch, 5);
		addChild(enemy1->enemy2IdleRightspritebatch, 5);
		addChild(enemy1->enemy2IdleLeftspritebatch, 5);
		addChild(enemy1->detect, 5);
		tag += 100;
		enemy1->enemyVisionCollider->setTag(tag);
		addChild(enemy1->enemyVision, 5);
		enemy1->enemy2WalkingRight->setPosition(enemy1->enemyArt->getPosition().x, enemy1->enemyArt->getPosition().y + 20);
		enemy1->enemy2WalkingLeft->setPosition(enemy1->enemyArt->getPosition().x, enemy1->enemyArt->getPosition().y + 20);
		enemy1->enemy2RunningRight->setPosition(enemy1->enemyArt->getPosition().x, enemy1->enemyArt->getPosition().y + 20);
		enemy1->enemy2RunningLeft->setPosition(enemy1->enemyArt->getPosition().x, enemy1->enemyArt->getPosition().y + 20);
		enemy1->enemy2IdleRight->setPosition(enemy1->enemyArt->getPosition().x, enemy1->enemyArt->getPosition().y + 20);
		enemy1->enemy2IdleLeft->setPosition(enemy1->enemyArt->getPosition().x, enemy1->enemyArt->getPosition().y + 20);

		enemy2 = new Enemy(31578, 31578, 2.0f, 20, 2);
		enemysVector.pushBack(enemy2);
		tag = 1000 + enemysVector.getIndex(enemy2);
		enemy2->enemyCollider->setTag(tag);
		enemy2->facingRight = false;
		enemy2->staticEnemy = true;
		addChild(enemy2->enemyArt, 5);
		addChild(enemy2->enemy2WalkingRightspritebatch, 5);
		addChild(enemy2->enemy2WalkingLeftspritebatch, 5);
		addChild(enemy2->enemy2RunningRightspritebatch, 5);
		addChild(enemy2->enemy2RunningLeftspritebatch, 5);
		addChild(enemy2->enemy2IdleRightspritebatch, 5);
		addChild(enemy2->enemy2IdleLeftspritebatch, 5);
		addChild(enemy2->detect, 5);
		tag += 100;
		enemy2->enemyVisionCollider->setTag(tag);
		addChild(enemy2->enemyVision, 5);
		enemy2->enemy2WalkingRight->setPosition(enemy2->enemyArt->getPosition().x, enemy2->enemyArt->getPosition().y + 20);
		enemy2->enemy2WalkingLeft->setPosition(enemy2->enemyArt->getPosition().x, enemy2->enemyArt->getPosition().y + 20);
		enemy2->enemy2RunningRight->setPosition(enemy2->enemyArt->getPosition().x, enemy2->enemyArt->getPosition().y + 20);
		enemy2->enemy2RunningLeft->setPosition(enemy2->enemyArt->getPosition().x, enemy2->enemyArt->getPosition().y + 20);
		enemy2->enemy2IdleRight->setPosition(enemy2->enemyArt->getPosition().x, enemy2->enemyArt->getPosition().y + 20);
		enemy2->enemy2IdleLeft->setPosition(enemy2->enemyArt->getPosition().x, enemy2->enemyArt->getPosition().y + 20);

		enemy3 = new Enemy(32341, 35043, 2.0f, 20, 2);
		enemysVector.pushBack(enemy3);
		tag = 1000 + enemysVector.getIndex(enemy3);
		enemy3->enemyCollider->setTag(tag);
		addChild(enemy3->enemyArt, 5);
		addChild(enemy3->enemy2WalkingRightspritebatch, 5);
		addChild(enemy3->enemy2WalkingLeftspritebatch, 5);
		addChild(enemy3->enemy2RunningRightspritebatch, 5);
		addChild(enemy3->enemy2RunningLeftspritebatch, 5);
		addChild(enemy3->enemy2IdleRightspritebatch, 5);
		addChild(enemy3->enemy2IdleLeftspritebatch, 5);
		addChild(enemy3->detect, 5);
		tag += 100;
		enemy3->enemyVisionCollider->setTag(tag);
		addChild(enemy3->enemyVision, 5);
		enemy3->enemy2WalkingRight->setPosition(enemy3->enemyArt->getPosition().x, enemy3->enemyArt->getPosition().y + 20);
		enemy3->enemy2WalkingLeft->setPosition(enemy3->enemyArt->getPosition().x, enemy3->enemyArt->getPosition().y + 20);
		enemy3->enemy2RunningRight->setPosition(enemy3->enemyArt->getPosition().x, enemy3->enemyArt->getPosition().y + 20);
		enemy3->enemy2RunningLeft->setPosition(enemy3->enemyArt->getPosition().x, enemy3->enemyArt->getPosition().y + 20);
		enemy3->enemy2IdleRight->setPosition(enemy3->enemyArt->getPosition().x, enemy3->enemyArt->getPosition().y + 20);
		enemy3->enemy2IdleLeft->setPosition(enemy3->enemyArt->getPosition().x, enemy3->enemyArt->getPosition().y + 20);

		/*enemy4 = new Enemy(35469, 36995, 2.0f, 20, 2);
		enemysVector.pushBack(enemy4);
		tag = 1000 + enemysVector.getIndex(enemy4);
		enemy4->enemyCollider->setTag(tag);
		addChild(enemy4->enemyArt, 5);
		addChild(enemy4->enemy2WalkingRightspritebatch, 5);
		addChild(enemy4->enemy2WalkingLeftspritebatch, 5);
		addChild(enemy4->enemy2RunningRightspritebatch, 5);
		addChild(enemy4->enemy2RunningLeftspritebatch, 5);
		addChild(enemy4->enemy2IdleRightspritebatch, 5);
		addChild(enemy4->enemy2IdleLeftspritebatch, 5);
		addChild(enemy4->detect, 5);
		tag += 100;
		enemy4->enemyVisionCollider->setTag(tag);
		addChild(enemy4->enemyVision, 5);
		enemy4->enemy2WalkingRight->setPosition(enemy4->enemyArt->getPosition().x, enemy4->enemyArt->getPosition().y + 20);
		enemy4->enemy2WalkingLeft->setPosition(enemy4->enemyArt->getPosition().x, enemy4->enemyArt->getPosition().y + 20);
		enemy4->enemy2RunningRight->setPosition(enemy4->enemyArt->getPosition().x, enemy4->enemyArt->getPosition().y + 20);
		enemy4->enemy2RunningLeft->setPosition(enemy4->enemyArt->getPosition().x, enemy4->enemyArt->getPosition().y + 20);
		enemy4->enemy2IdleRight->setPosition(enemy4->enemyArt->getPosition().x, enemy4->enemyArt->getPosition().y + 20);
		enemy4->enemy2IdleLeft->setPosition(enemy4->enemyArt->getPosition().x, enemy4->enemyArt->getPosition().y + 20);*/

		/*enemy5 = new Enemy(37258, 38888, 2.0f, 20, 2);
		enemysVector.pushBack(enemy5);
		tag = 1000 + enemysVector.getIndex(enemy5);
		enemy5->enemyCollider->setTag(tag);
		addChild(enemy5->enemyArt, 5);
		addChild(enemy5->enemy2WalkingRightspritebatch, 5);
		addChild(enemy5->enemy2WalkingLeftspritebatch, 5);
		addChild(enemy5->enemy2RunningRightspritebatch, 5);
		addChild(enemy5->enemy2RunningLeftspritebatch, 5);
		addChild(enemy5->enemy2IdleRightspritebatch, 5);
		addChild(enemy5->enemy2IdleLeftspritebatch, 5);
		addChild(enemy5->detect, 5);
		tag += 100;
		enemy5->enemyVisionCollider->setTag(tag);
		addChild(enemy5->enemyVision, 5);
		enemy5->enemy2WalkingRight->setPosition(enemy5->enemyArt->getPosition().x, enemy5->enemyArt->getPosition().y + 20);
		enemy5->enemy2WalkingLeft->setPosition(enemy5->enemyArt->getPosition().x, enemy5->enemyArt->getPosition().y + 20);
		enemy5->enemy2RunningRight->setPosition(enemy5->enemyArt->getPosition().x, enemy5->enemyArt->getPosition().y + 20);
		enemy5->enemy2RunningLeft->setPosition(enemy5->enemyArt->getPosition().x, enemy5->enemyArt->getPosition().y + 20);
		enemy5->enemy2IdleRight->setPosition(enemy5->enemyArt->getPosition().x, enemy5->enemyArt->getPosition().y + 20);
		enemy5->enemy2IdleLeft->setPosition(enemy5->enemyArt->getPosition().x, enemy5->enemyArt->getPosition().y + 20);*/

		/*enemy6 = new Enemy(34670, 34670, 2.0f, 20, 2);
		enemysVector.pushBack(enemy6);
		tag = 1000 + enemysVector.getIndex(enemy6);
		enemy6->enemyCollider->setTag(tag);
		enemy6->facingRight = true;
		enemy6->staticEnemy = true;
		enemy6->enemyArt->setPositionY(1303);
		addChild(enemy6->enemyArt, 5);
		addChild(enemy6->enemy2WalkingRightspritebatch, 5);
		addChild(enemy6->enemy2WalkingLeftspritebatch, 5);
		addChild(enemy6->enemy2RunningRightspritebatch, 5);
		addChild(enemy6->enemy2RunningLeftspritebatch, 5);
		addChild(enemy6->enemy2IdleRightspritebatch, 5);
		addChild(enemy6->enemy2IdleLeftspritebatch, 5);
		addChild(enemy6->detect, 5);
		tag += 100;
		enemy6->enemyVisionCollider->setTag(tag);
		addChild(enemy6->enemyVision, 5);
		enemy6->enemy2WalkingRight->setPosition(enemy6->enemyArt->getPosition().x, enemy6->enemyArt->getPosition().y + 20);
		enemy6->enemy2WalkingLeft->setPosition(enemy6->enemyArt->getPosition().x, enemy6->enemyArt->getPosition().y + 20);
		enemy6->enemy2RunningRight->setPosition(enemy6->enemyArt->getPosition().x, enemy6->enemyArt->getPosition().y + 20);
		enemy6->enemy2RunningLeft->setPosition(enemy6->enemyArt->getPosition().x, enemy6->enemyArt->getPosition().y + 20);
		enemy6->enemy2IdleRight->setPosition(enemy6->enemyArt->getPosition().x, enemy6->enemyArt->getPosition().y + 20);
		enemy6->enemy2IdleLeft->setPosition(enemy6->enemyArt->getPosition().x, enemy6->enemyArt->getPosition().y + 20);

		enemy7 = new Enemy(36873, 37774, 2.0f, 20, 2);
		enemysVector.pushBack(enemy7);
		tag = 1000 + enemysVector.getIndex(enemy7);
		enemy7->enemyCollider->setTag(tag);
		enemy7->enemyArt->setPositionY(708);
		addChild(enemy7->enemyArt, 5);
		addChild(enemy7->enemy2WalkingRightspritebatch, 5);
		addChild(enemy7->enemy2WalkingLeftspritebatch, 5);
		addChild(enemy7->enemy2RunningRightspritebatch, 5);
		addChild(enemy7->enemy2RunningLeftspritebatch, 5);
		addChild(enemy7->enemy2IdleRightspritebatch, 5);
		addChild(enemy7->enemy2IdleLeftspritebatch, 5);
		addChild(enemy7->detect, 5);
		tag += 100;
		enemy7->enemyVisionCollider->setTag(tag);
		addChild(enemy7->enemyVision, 5);
		enemy7->enemy2WalkingRight->setPosition(enemy7->enemyArt->getPosition().x, enemy7->enemyArt->getPosition().y + 20);
		enemy7->enemy2WalkingLeft->setPosition(enemy7->enemyArt->getPosition().x, enemy7->enemyArt->getPosition().y + 20);
		enemy7->enemy2RunningRight->setPosition(enemy7->enemyArt->getPosition().x, enemy7->enemyArt->getPosition().y + 20);
		enemy7->enemy2RunningLeft->setPosition(enemy7->enemyArt->getPosition().x, enemy7->enemyArt->getPosition().y + 20);
		enemy7->enemy2IdleRight->setPosition(enemy7->enemyArt->getPosition().x, enemy7->enemyArt->getPosition().y + 20);
		enemy7->enemy2IdleLeft->setPosition(enemy7->enemyArt->getPosition().x, enemy7->enemyArt->getPosition().y + 20);*/

		/*enemy3 = new Enemy(14381 + 9000, 14381 + 7750, 2.0f, 4, 1);
		enemysVector.pushBack(enemy3);
		tag = 1000 + enemysVector.getIndex(enemy3);
		enemy3->enemyCollider->setTag(tag);
		addChild(enemy3->enemyArt, 5);
		addChild(enemy3->detect, 5);
		tag += 100;
		enemy3->enemyVisionCollider->setTag(tag);
		addChild(enemy3->enemyVision, 5);

		enemy4 = new Enemy(14381 + 10200, 14381 + 10200, 2.0f, 5, 1);
		enemysVector.pushBack(enemy4);
		tag = 1000 + enemysVector.getIndex(enemy4);
		enemy4->enemyCollider->setTag(tag);
		addChild(enemy4->enemyArt, 5);
		addChild(enemy4->detect, 5);
		tag += 100;
		enemy4->enemyVisionCollider->setTag(tag);
		addChild(enemy4->enemyVision, 5);*/
	}

	/*if (Iniko->characterIdleRight->getPositionX() > (14381 + 13570))
	{
	gameOver();
	}*/

	//EVENTS

	//Z ORDER FIX

	if (contactFloor != NULL && Iniko->characterVision->getPosition().y > 300)
	{
		/*Iniko->runningSoundColliderSprite->setZOrder(4);
		Iniko->characterIdlerightspritebatch->setZOrder(4);
		Iniko->characterRunningRightspritebatch->setZOrder(4);
		Iniko->characterIdleleftspritebatch->setZOrder(4);
		Iniko->characterRunningLeftspritebatch->setZOrder(4);
		Iniko->characterVision->setZOrder(4);
		Iniko->AKey->setZOrder(4);
		Iniko->SKey->setZOrder(4);*/
	}

	//Z ODER FIX

	//PARALLAX

	Layer0->setPosition(Point((Layer0->getContentSize().width / 2) - 3000 + Iniko->characterVision->getPosition().x, (Layer0->getContentSize().height / 2)));
	Layer1->setPosition(Point((Layer1->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.05, (Layer1->getContentSize().height / 2)));
	Layer2->setPosition(Point((Layer2->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.06, (Layer2->getContentSize().height / 2)));
	Layer3->setPosition(Point((Layer3->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.07, (Layer3->getContentSize().height / 2)));
	//Layer4->setPosition(Point((Layer4->getContentSize().width / 2) - 2000 + Iniko->characterVision->getPosition().x - Iniko->characterVision->getPosition().x * 0.7, (Layer4->getContentSize().height / 2)));*/

	//PARALLAX

	//POWER UPS UPDATE

	power1->flyParticleSmoke->setPosition(power1->flyParticle->getPosition());

	if (!power1->activated && !power1->finish)
	{
		power1->flyParticle->setPosition(Iniko->characterVision->getPosition());
	}

	else if (power1->activated && !power1->finish)
	{
		if (power1->flyParticle->getPosition().x >= power1->initialPos + 3000)
		{
			power1->finish = true;
			power1->activated = false;
			power1->flyParticleCollider->setEnable(false);
		}

		else if (power1->flyParticle->getPosition().x <= power1->initialPos - 3000)
		{
			power1->finish = true;
			power1->activated = false;
			power1->flyParticleCollider->setEnable(false);
		}

		if (power1->rightDirection)
		{
			power1->flyParticle->setPositionX(power1->flyParticle->getPosition().x + (800 * dt));
		}

		else if (!power1->rightDirection)
		{
			power1->flyParticle->setPositionX(power1->flyParticle->getPosition().x - (800 * dt));
		}
	}

	else if (power1->finish && !power1->activated)
	{
		if (power1->flyParticle->getPosition().y < 3000)
			power1->flyParticle->setPositionY(power1->flyParticle->getPosition().y + (600 * dt));
	}

	power2->shadowParticle->setPosition(Iniko->characterVision->getPosition());

	if (!power2->activated && power2->finish)
	{
		power2->shadowParticle->setDuration(0);
		power2->shadowParticle->setGravity(Vec2(-100, 0));

		Iniko->runningSoundCollider->setEnable(true);
		Iniko->characterIdleRight->setOpacity(255);
		Iniko->characterIdleRightCollider->setEnable(true);
		Iniko->characterIdleLeft->setOpacity(255);
		Iniko->characterIdleLeftCollider->setEnable(true);
		Iniko->characterRunningRight->setOpacity(255);
		Iniko->characterRunningRightCollider->setEnable(true);
		Iniko->characterRunningLeft->setOpacity(255);
		Iniko->characterRunningLeftCollider->setEnable(true);
	}

	//POWERS UPDATE

	//FACING UPDATE

	if (Iniko->facingRight && !moveRight && !moveLeft /*&& !Iniko->jumping*/)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterStealthRightspritebatch->setVisible(false);
		Iniko->characterStealthLeftspritebatch->setVisible(false);
	}

	if (!Iniko->facingRight && !moveRight && !moveLeft/* && !Iniko->jumping*/)
	{
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(true);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterStealthRightspritebatch->setVisible(false);
		Iniko->characterStealthLeftspritebatch->setVisible(false);
	}

	//FACING UPDATE

	//ENEMY MOVEMENT

	for (int i = 0; i < enemysVector.size(); i++)
	{
		if (enemysVector.at(i)->die && enemysVector.at(i)->enemyArt->getNumberOfRunningActions() == 0)
		{
			enemysVector.at(i)->enemyArt->setVisible(false);
		}

		if (!enemysVector.at(i)->die && !enemysVector.at(i)->stunned && !Iniko->gameOver)
		{
			enemysVector.at(i)->moveVision();

			if (enemysVector.at(i)->type == 1)
			{
				enemysVector.at(i)->enemy1WalkingRight->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemy1WalkingLeft->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemy1RunningRight->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y);
				enemysVector.at(i)->enemy1RunningLeft->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y);
				enemysVector.at(i)->enemy1IdleRight->setPosition(enemysVector.at(i)->enemyArt->getPosition().x - 20, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemy1IdleLeft->setPosition(enemysVector.at(i)->enemyArt->getPosition().x + 20, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemyArt->setPosition(enemysVector.at(i)->enemyArt->getPosition());
			}

			else if (enemysVector.at(i)->type == 2)
			{
				enemysVector.at(i)->enemy2WalkingRight->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemy2WalkingLeft->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemy2RunningRight->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y);
				enemysVector.at(i)->enemy2RunningLeft->setPosition(enemysVector.at(i)->enemyArt->getPosition().x, enemysVector.at(i)->enemyArt->getPosition().y);
				enemysVector.at(i)->enemy2IdleRight->setPosition(enemysVector.at(i)->enemyArt->getPosition().x - 20, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemy2IdleLeft->setPosition(enemysVector.at(i)->enemyArt->getPosition().x + 20, enemysVector.at(i)->enemyArt->getPosition().y - 10);
				enemysVector.at(i)->enemyArt->setPosition(enemysVector.at(i)->enemyArt->getPosition());
			}

			if (enemysVector.at(i)->stopped)
			{
				if (enemysVector.at(i)->type == 1)
				{
					if (enemysVector.at(i)->facingRight)
					{
						enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1IdleRightspritebatch->setVisible(true);
						enemysVector.at(i)->enemy1IdleLeftspritebatch->setVisible(false);
					}

					else
					{
						enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1IdleRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1IdleLeftspritebatch->setVisible(true);
					}
				}

				else
				{
					if (enemysVector.at(i)->facingRight)
					{
						enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2IdleRightspritebatch->setVisible(true);
						enemysVector.at(i)->enemy2IdleLeftspritebatch->setVisible(false);
					}

					else
					{
						enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2IdleRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2IdleLeftspritebatch->setVisible(true);
					}
				}
			}

			else
			{
				if (enemysVector.at(i)->facingRight)
				{
					if (enemysVector.at(i)->type == 1)
					{
						if (enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posInitial || enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posFinal)
						{
							enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1IdleRightspritebatch->setVisible(true);
							enemysVector.at(i)->enemy1IdleLeftspritebatch->setVisible(false);
						}

						else
						{
							enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(true);
							enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1IdleRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1IdleLeftspritebatch->setVisible(false);
						}
					}

					else if (enemysVector.at(i)->type == 2)
					{
						if (enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posInitial || enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posFinal)
						{
							enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2IdleRightspritebatch->setVisible(true);
							enemysVector.at(i)->enemy2IdleLeftspritebatch->setVisible(false);
						}

						else
						{
							enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(true);
							enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2IdleRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2IdleLeftspritebatch->setVisible(false);
						}
					}

					enemysVector.at(i)->enemyArt->setVisible(false);
				}

				else
				{
					if (enemysVector.at(i)->type == 1)
					{
						if (enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posInitial || enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posFinal)
						{
							enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1IdleRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1IdleLeftspritebatch->setVisible(true);
						}

						else
						{
							enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(true);
							enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1IdleRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1IdleLeftspritebatch->setVisible(false);
						}
					}

					else if (enemysVector.at(i)->type == 2)
					{
						if (enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posInitial || enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posFinal)
						{
							enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2IdleRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2IdleLeftspritebatch->setVisible(true);
						}

						else
						{
							enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(true);
							enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2IdleRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2IdleLeftspritebatch->setVisible(false);
						}
					}

					enemysVector.at(i)->enemyArt->setVisible(false);
				}
			}

			if (enemysVector.at(i)->alertedEnemy)
			{
				enemysVector.at(i)->stopped = false;

				if (enemysVector.at(i)->facingRight)
				{
					if (enemysVector.at(i)->type == 1)
					{
						if (enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posInitial || enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posFinal)
						{
							enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
						}

						else
						{
							enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(true);
							enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
						}
					}

					else if (enemysVector.at(i)->type == 2)
					{
						if (enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posInitial || enemysVector.at(i)->enemyArt->getPosition().x == enemysVector.at(i)->posFinal)
						{
							enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
						}

						else
						{
							enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
							enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(true);
							enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
						}
					}
				}

				else
				{
					if (enemysVector.at(i)->type == 1)
					{
						enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(true);
					}

					else if (enemysVector.at(i)->type == 2)
					{
						enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(true);
					}
				}

				enemysVector.at(i)->alertedSound = false;
				enemysVector.at(i)->followPos = Iniko->characterIdleRight->getPosition().x;
				enemysVector.at(i)->enemyArt->stopAction(enemysVector.at(i)->sequence);
				enemysVector.at(i)->detectCharacter(dt);
			}

			else if (enemysVector.at(i)->alertedSound)
			{
				enemysVector.at(i)->stopped = false;

				if (enemysVector.at(i)->facingRight)
				{
					if (enemysVector.at(i)->type == 1)
					{
						enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(true);
						enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
					}

					else if (enemysVector.at(i)->type == 2)
					{
						enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(true);
						enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
					}
				}

				else
				{
					if (enemysVector.at(i)->type == 1)
					{
						enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(true);
					}

					else if (enemysVector.at(i)->type == 2)
					{
						enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(true);
					}
				}

				enemysVector.at(i)->enemyArt->stopAction(enemysVector.at(i)->sequence);
				enemysVector.at(i)->detectCharacter(dt);
			}

			else if (enemysVector.at(i)->returning)
			{
				enemysVector.at(i)->stopped = false;

				if (enemysVector.at(i)->facingRight)
				{
					if (enemysVector.at(i)->type == 1)
					{
						enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(true);
						enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
					}

					else if (enemysVector.at(i)->type == 2)
					{
						enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(true);
						enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
					}
				}

				else
				{
					if (enemysVector.at(i)->type == 1)
					{
						enemysVector.at(i)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1WalkingLeftspritebatch->setVisible(true);
						enemysVector.at(i)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy1RunningLeftspritebatch->setVisible(false);
					}

					else if (enemysVector.at(i)->type == 2)
					{
						enemysVector.at(i)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2WalkingLeftspritebatch->setVisible(true);
						enemysVector.at(i)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(i)->enemy2RunningLeftspritebatch->setVisible(false);
					}
				}

				enemysVector.at(i)->detectCharacter(dt);
			}
		}
	}

	//ENEMY MOVEMENT

	//GENERAL MOVEMENT

	if (moveRight && moveLeft && !moveCam && !Iniko->stealth && !Iniko->hide)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterStealthRightspritebatch->setVisible(false);
		Iniko->characterStealthLeftspritebatch->setVisible(false);
	}

	/*else if (moveCam)
	{
	if (Iniko->facingRight)
	{
	Iniko->characterIdlerightspritebatch->setVisible(true);
	Iniko->characterIdleleftspritebatch->setVisible(false);
	Iniko->characterRunningRightspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(false);
	}

	else
	{
	Iniko->characterIdlerightspritebatch->setVisible(false);
	Iniko->characterIdleleftspritebatch->setVisible(true);
	Iniko->characterRunningRightspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(false);
	}
	}*/

	else if (moveRight && !moveCam && !Iniko->stealth && !Iniko->hide /*&& !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = true;

			//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = 1;

			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(true);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
			Iniko->characterStealthRightspritebatch->setVisible(false);
			Iniko->characterStealthLeftspritebatch->setVisible(false);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(true);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(true);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				//Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));
				Iniko->characterStealthRightCollider->setVelocity(Vec2(0, Iniko->characterStealthRightCollider->getVelocity().y));
				Iniko->characterStealthLeftCollider->setVelocity(Vec2(0, Iniko->characterStealthLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	else if (moveLeft && !moveCam && !Iniko->stealth && !Iniko->hide/* && !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = false;

			//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = -1;

			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(true);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
			Iniko->characterStealthRightspritebatch->setVisible(false);
			Iniko->characterStealthLeftspritebatch->setVisible(false);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(true);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -1;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(true);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));
				Iniko->characterStealthRightCollider->setVelocity(Vec2(0, Iniko->characterStealthRightCollider->getVelocity().y));
				Iniko->characterStealthLeftCollider->setVelocity(Vec2(0, Iniko->characterStealthLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	else
		Iniko->velocity = 0;

	//GENERAL MOVEMENT

	//STEALTH MOVEMENT

	if (moveLeft && moveRight && !moveCam && Iniko->stealth && !Iniko->hide)
	{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterStealthRightspritebatch->setVisible(false);
		Iniko->characterStealthLeftspritebatch->setVisible(false);
	}

	else if (moveRight && !moveCam && Iniko->stealth && !Iniko->hide /*&& !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = true;

			//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = 0.5;

			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(false);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
			Iniko->characterStealthRightspritebatch->setVisible(true);
			Iniko->characterStealthLeftspritebatch->setVisible(false);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(true);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = true;

				//Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition().x + (800 * dt), Iniko->characterIdleRight->getPosition().y);
				//Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(true);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				//Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(true);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));
				Iniko->characterStealthRightCollider->setVelocity(Vec2(0, Iniko->characterStealthRightCollider->getVelocity().y));
				Iniko->characterStealthLeftCollider->setVelocity(Vec2(0, Iniko->characterStealthLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	else if (moveLeft && !moveCam && Iniko->stealth && !Iniko->hide/* && !Iniko->jumping*/)
	{
		if (Iniko->wallTouch == NULL)
		{
			Iniko->facingRight = false;

			//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

			Iniko->velocity = -0.5;

			Iniko->characterIdlerightspritebatch->setVisible(false);
			Iniko->characterIdleleftspritebatch->setVisible(false);
			Iniko->characterRunningRightspritebatch->setVisible(false);
			Iniko->characterRunningLeftspritebatch->setVisible(false);
			Iniko->characterJumpingLeft->setVisible(false);
			Iniko->characterJumpingRight->setVisible(false);
			Iniko->characterStealthRightspritebatch->setVisible(false);
			Iniko->characterStealthLeftspritebatch->setVisible(true);
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'L')
		{
			if (!Iniko->jumping)
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(true);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}

			else
			{
				Iniko->facingRight = false;

				//Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition().x - (800 * dt), Iniko->characterIdleLeft->getPosition().y);
				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(-500, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = -0.5;

				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->wallTouch = NULL;
				Iniko->wallTouchSide = ' ';
			}
		}

		else if (Iniko->wallTouch != NULL && Iniko->wallTouchSide == 'R')
		{
			if (!Iniko->jumping)
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(true);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				//Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				/*Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));*/

				Iniko->velocity = 0;
			}

			else
			{
				Iniko->characterIdlerightspritebatch->setVisible(false);
				Iniko->characterIdleleftspritebatch->setVisible(false);
				Iniko->characterRunningLeftspritebatch->setVisible(false);
				Iniko->characterRunningRightspritebatch->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(true);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterStealthRightspritebatch->setVisible(false);
				Iniko->characterStealthLeftspritebatch->setVisible(false);

				Iniko->characterJumpingRightCollider->setVelocity(Vec2(0, Iniko->characterJumpingRightCollider->getVelocity().y));
				Iniko->characterJumpingLeftCollider->setVelocity(Vec2(0, Iniko->characterJumpingLeftCollider->getVelocity().y));
				Iniko->characterRunningRightCollider->setVelocity(Vec2(0, Iniko->characterRunningRightCollider->getVelocity().y));
				Iniko->characterRunningLeftCollider->setVelocity(Vec2(0, Iniko->characterRunningLeftCollider->getVelocity().y));
				Iniko->characterIdleRightCollider->setVelocity(Vec2(0, Iniko->characterIdleRightCollider->getVelocity().y));
				Iniko->characterIdleLeftCollider->setVelocity(Vec2(0, Iniko->characterIdleLeftCollider->getVelocity().y));
				Iniko->characterStealthRightCollider->setVelocity(Vec2(0, Iniko->characterStealthRightCollider->getVelocity().y));
				Iniko->characterStealthLeftCollider->setVelocity(Vec2(0, Iniko->characterStealthLeftCollider->getVelocity().y));

				Iniko->velocity = 0;
			}
		}
	}

	//STEALTH MOVEMENT

	//STOPS IF MOVE IN TWO DIRECTIONS

	if (moveLeft && moveRight)
	{
		Iniko->facingRight = true;
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterStealthRightspritebatch->setVisible(false);
		Iniko->characterStealthLeftspritebatch->setVisible(false);
	}

	//STOPS IF MOVE IN TWO DIRECTIONS

	//CHARACTER ART UPDATE

	/*if (Iniko->characterJumpingRight->getPosition().y < 100 || Iniko->characterJumpingLeft->getPosition().y < 100)
	{
	Iniko->characterIdleRight->setPosition(Point(Iniko->initposx, Iniko->initposy));
	Iniko->characterIdleLeft->setPosition(Point(Iniko->initposx, Iniko->initposy));
	Iniko->characterRunningRight->setPosition(Point(Iniko->initposx, Iniko->initposy));
	Iniko->characterRunningLeft->setPosition(Point(Iniko->initposx, Iniko->initposy));
	Iniko->characterJumpingRight->setPosition(Point(Iniko->initposx, Iniko->initposy));
	Iniko->characterJumpingLeft->setPosition(Point(Iniko->initposx, Iniko->initposy));

	Iniko->jumping = true;
	Iniko->stealth = false;

	Iniko->characterJumpingRight->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

	//Iniko->characterJumpingRightCollider->setGravityEnable(true);
	Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 750));

	Iniko->characterJumpingLeft->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

	//Iniko->characterJumpingLeftCollider->setGravityEnable(true);
	Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 750));

	}*/

	if (Iniko->facingRight)
	{
		if (Iniko->jumping || contactFloor == NULL)
		{
			Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterJumpingRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterJumpingLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 150));
			Iniko->characterStealthRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterStealthLeft->setPosition(Iniko->characterJumpingRight->getPosition());
		}

		else
		{
			if (!Iniko->stealth)
			{
				Iniko->runningSoundColliderSprite->setPosition(Iniko->characterRunningRight->getPosition());
				Iniko->characterRunningLeft->setPosition(Iniko->characterRunningRight->getPosition());
				Iniko->characterRunningRight->setPosition(Iniko->characterRunningRight->getPosition());
				Iniko->characterIdleLeft->setPosition(Iniko->characterRunningRight->getPosition());
				Iniko->characterIdleRight->setPosition(Iniko->characterRunningRight->getPosition());
				Iniko->characterJumpingRight->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y);
				Iniko->characterJumpingLeft->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y);
				Iniko->characterVision->setPosition(Iniko->characterRunningRight->getPosition());
				Iniko->AKey->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + (Iniko->characterRunningRight->getContentSize().height / 2 + 80));
				Iniko->SKey->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + (Iniko->characterRunningRight->getContentSize().height / 2 + 150));
				Iniko->characterStealthRight->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y - 49);
				Iniko->characterStealthLeft->setPosition(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y - 49);
			}

			else
			{
				Iniko->runningSoundColliderSprite->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterRunningLeft->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterRunningRight->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterIdleLeft->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterIdleRight->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterJumpingRight->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterJumpingLeft->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterVision->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->AKey->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y + (Iniko->characterStealthRight->getContentSize().height / 2 + 80));
				Iniko->SKey->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y + (Iniko->characterStealthRight->getContentSize().height / 2 + 150));
				Iniko->characterStealthRight->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
				Iniko->characterStealthLeft->setPosition(Iniko->characterStealthRight->getPosition().x, Iniko->characterStealthRight->getPosition().y);
			}
		}

		/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterRunningLeft->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterRunningRight->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterIdleRight->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->characterVision->setPosition(Iniko->characterIdleRight->getPosition());
		Iniko->AKey->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + (Iniko->characterIdleRight->getContentSize().height / 2 + 80));
		Iniko->SKey->setPosition(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + (Iniko->characterIdleRight->getContentSize().height / 2 + 150));*/
	}

	else if (!Iniko->facingRight)
	{
		if (Iniko->jumping || contactFloor == NULL)
		{
			Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterJumpingRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterJumpingLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 150));
			Iniko->characterStealthRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterStealthLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
		}

		else
		{
			if (!Iniko->stealth)
			{
				Iniko->runningSoundColliderSprite->setPosition(Iniko->characterRunningLeft->getPosition());
				Iniko->characterRunningLeft->setPosition(Iniko->characterRunningLeft->getPosition());
				Iniko->characterRunningRight->setPosition(Iniko->characterRunningLeft->getPosition());
				Iniko->characterIdleLeft->setPosition(Iniko->characterRunningLeft->getPosition());
				Iniko->characterIdleRight->setPosition(Iniko->characterRunningLeft->getPosition());
				Iniko->characterJumpingRight->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y);
				Iniko->characterJumpingLeft->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y);
				Iniko->characterVision->setPosition(Iniko->characterRunningLeft->getPosition());
				Iniko->AKey->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + (Iniko->characterRunningLeft->getContentSize().height / 2 + 80));
				Iniko->SKey->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + (Iniko->characterRunningLeft->getContentSize().height / 2 + 150));
				Iniko->characterStealthRight->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y - 49);
				Iniko->characterStealthLeft->setPosition(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y - 49);
			}

			else
			{
				Iniko->runningSoundColliderSprite->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterRunningLeft->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterRunningRight->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterIdleLeft->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterIdleRight->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterJumpingRight->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterJumpingLeft->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterVision->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->AKey->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y + (Iniko->characterStealthLeft->getContentSize().height / 2 + 80));
				Iniko->SKey->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y + (Iniko->characterStealthLeft->getContentSize().height / 2 + 150));
				Iniko->characterStealthRight->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
				Iniko->characterStealthLeft->setPosition(Iniko->characterStealthLeft->getPosition().x, Iniko->characterStealthLeft->getPosition().y);
			}
		}

		/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterRunningLeft->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterRunningRight->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterIdleLeft->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterIdleRight->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->characterVision->setPosition(Iniko->characterIdleLeft->getPosition());
		Iniko->AKey->setPosition(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + (Iniko->characterIdleLeft->getContentSize().height / 2 + 80));
		Iniko->SKey->setPosition(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + (Iniko->characterIdleLeft->getContentSize().height / 2 + 150));*/
	}

	//CHARACTER ART UPDATE

	//SALTO UPDATE

	/*if (Iniko->jumping)
	{
	if (Iniko->facingRight)
	{
	Iniko->characterIdlerightspritebatch->setVisible(false);
	Iniko->characterIdleleftspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(false);
	Iniko->characterRunningRightspritebatch->setVisible(true);
	}

	else if (!Iniko->facingRight)
	{
	Iniko->characterIdlerightspritebatch->setVisible(false);
	Iniko->characterIdleleftspritebatch->setVisible(false);
	Iniko->characterRunningLeftspritebatch->setVisible(true);
	Iniko->characterRunningRightspritebatch->setVisible(false);
	}
	}*/

	//WALL COLLISION

	if (Iniko->wallTouch != NULL)
	{
		if (!Iniko->facingRight && (Iniko->characterIdleLeft->getPosition().x - Iniko->characterIdleLeft->getContentSize().width / 2) > (Iniko->wallTouch->getPosition().x + Iniko->wallTouch->getContentSize().width / 2))
		{
			Iniko->wallTouchSide = 'R';
		}

		else if (Iniko->facingRight && (Iniko->characterIdleRight->getPosition().x + Iniko->characterIdleLeft->getContentSize().width / 2) < (Iniko->wallTouch->getPosition().x - Iniko->wallTouch->getContentSize().width / 2))
		{
			Iniko->wallTouchSide = 'L';
		}
	}

	//JUMPING UPDATE

	if (Iniko->jumping || (Iniko->characterJumpingRightCollider->getVelocity().y < 0) || (Iniko->characterJumpingLeftCollider->getVelocity().y < 0))
	{
		Iniko->characterIdleLeftCollider->setGravityEnable(true);
		Iniko->characterIdleRightCollider->setGravityEnable(true);
		Iniko->characterRunningRightCollider->setGravityEnable(true);
		Iniko->characterRunningLeftCollider->setGravityEnable(true);
		Iniko->characterJumpingRightCollider->setGravityEnable(true);
		Iniko->characterJumpingLeftCollider->setGravityEnable(true);
		Iniko->characterStealthRightCollider->setGravityEnable(true);
		Iniko->characterStealthLeftCollider->setGravityEnable(true);

		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterStealthRightspritebatch->setVisible(false);
		Iniko->characterStealthLeftspritebatch->setVisible(false);

		if (Iniko->facingRight)
		{
			Iniko->characterJumpingRight->setVisible(true);
			Iniko->characterJumpingLeft->setVisible(false);

			/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingRight->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingRight->getPosition().x, Iniko->characterJumpingRight->getPosition().y + (Iniko->characterJumpingRight->getContentSize().height / 2 + 150));*/
		}

		else
		{
			Iniko->characterJumpingRight->setVisible(false);
			Iniko->characterJumpingLeft->setVisible(true);

			/*Iniko->runningSoundColliderSprite->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterRunningRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleLeft->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterIdleRight->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->characterVision->setPosition(Iniko->characterJumpingLeft->getPosition());
			Iniko->AKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 80));
			Iniko->SKey->setPosition(Iniko->characterJumpingLeft->getPosition().x, Iniko->characterJumpingLeft->getPosition().y + (Iniko->characterJumpingLeft->getContentSize().height / 2 + 150));*/
		}
	}

	if (key == 'S' && !Iniko->jumping && Iniko->characterJumpingLeftCollider->getVelocity().y >= 0 && Iniko->characterJumpingRightCollider->getVelocity().y >= 0)
	{
		if (Iniko->facingRight)
		{
			//moveCam = true;

			/*Iniko->runningSoundColliderSprite->setZOrder(4);
			Iniko->characterIdlerightspritebatch->setZOrder(4);
			Iniko->characterRunningRightspritebatch->setZOrder(4);
			Iniko->characterIdleleftspritebatch->setZOrder(4);
			Iniko->characterRunningLeftspritebatch->setZOrder(4);
			Iniko->characterVision->setZOrder(4);
			Iniko->AKey->setZOrder(4);
			Iniko->SKey->setZOrder(4);*/

			Iniko->jumping = true;
			Iniko->stealth = false;

			Iniko->characterJumpingRight->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

			//Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 750));

			Iniko->characterJumpingLeft->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

			//Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 750));
			/*
			//Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 5));
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));
			//Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));

			//Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, Iniko->characterRunningLeft->getPosition().y + 5));
			//Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));

			//Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + 5));
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterIdleRightCollider->getVelocity().x, 500));
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));

			//Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + 5));
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterIdleLeftCollider->getVelocity().x, 500));
			Iniko->characterIdleLeftCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));*/
		}

		if (!Iniko->facingRight)
		{
			//moveCam = true;

			/*Iniko->runningSoundColliderSprite->setZOrder(4);
			Iniko->characterIdlerightspritebatch->setZOrder(4);
			Iniko->characterRunningRightspritebatch->setZOrder(4);
			Iniko->characterIdleleftspritebatch->setZOrder(4);
			Iniko->characterRunningLeftspritebatch->setZOrder(4);
			Iniko->characterVision->setZOrder(4);
			Iniko->AKey->setZOrder(4);
			Iniko->SKey->setZOrder(4);*/

			Iniko->jumping = true;

			Iniko->characterJumpingLeft->setPositionY(Iniko->characterRunningLeft->getPosition().y + 50);

			//Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 750));

			Iniko->characterJumpingRight->setPositionY(Iniko->characterRunningRight->getPosition().y + 50);

			//Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 750));
			/*
			//Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 5));
			//Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningRightCollider->getVelocity().x, 500));
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));

			//Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningRight->getPosition().x, Iniko->characterRunningRight->getPosition().y + 5));
			//Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));

			//Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + 5));
			//Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterIdleRightCollider->getVelocity().x, 500));
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));

			//Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + 5));
			//Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterIdleLeftCollider->getVelocity().x, 500));
			Iniko->characterIdleLeftCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterRunningLeftCollider->getVelocity().x, 500));*/
		}
	}

	/*if (Iniko->SKey->isVisible())
	{
	if (key == 'S')
	{
	//moveRight = false;
	//moveLeft = false;
	moveCam = true;

	Iniko->runningSoundColliderSprite->setZOrder(4);
	Iniko->characterIdlerightspritebatch->setZOrder(4);
	Iniko->characterRunningRightspritebatch->setZOrder(4);
	Iniko->characterIdleleftspritebatch->setZOrder(4);
	Iniko->characterRunningLeftspritebatch->setZOrder(4);
	Iniko->characterVision->setZOrder(4);
	Iniko->AKey->setZOrder(4);
	Iniko->SKey->setZOrder(4);

	Iniko->jumping = true;

	if (Iniko->facingRight)
	{
	Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, Iniko->characterIdleRight->getPosition().y + 5));
	Iniko->characterIdleRightCollider->setVelocity(objectsVector.at(contactBody->getTag() - 4000)->force);
	}

	else
	{
	Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, Iniko->characterIdleLeft->getPosition().y + 5));
	Iniko->characterIdleLeftCollider->setVelocity(objectsVector.at(contactBody->getTag() - 4000)->force);
	}
	}
	}*/

	//FALLING UPDATE

	//if (Iniko->characterJumpingRightCollider->getVelocity().y < 0 || Iniko->characterJumpingLeftCollider->getVelocity().y < 0)
	//{
		/*if (Iniko->characterIdleRightCollider->getVelocity().x == 0 && Iniko->characterIdleLeftCollider->getVelocity().x == 0)
		{
		Iniko->runningSoundColliderSprite->setZOrder(5);
		Iniko->characterIdlerightspritebatch->setZOrder(5);
		Iniko->characterRunningRightspritebatch->setZOrder(5);
		Iniko->characterIdleleftspritebatch->setZOrder(5);
		Iniko->characterRunningLeftspritebatch->setZOrder(5);
		Iniko->characterVision->setZOrder(5);
		Iniko->AKey->setZOrder(5);
		Iniko->SKey->setZOrder(5);
		}*/

		//Iniko->jumping = false;

		/*if (Iniko->facingRight)
		{
		Iniko->characterIdlerightspritebatch->setVisible(true);
		Iniko->characterIdleleftspritebatch->setVisible(false);
		}

		else
		{
		Iniko->characterIdlerightspritebatch->setVisible(false);
		Iniko->characterIdleleftspritebatch->setVisible(true);
		}

		//moveRight = false;
		//moveLeft = false;
		//moveCam = true;
		Iniko->characterRunningLeftspritebatch->setVisible(false);
		Iniko->characterRunningRightspritebatch->setVisible(false);*/
	//}

	//FALLING UPDATE

	//KEY PRESSED HANDLER

	if (key == 'W' && (contactBody->getTag() / 100) == 20)
	{
		moveCam = true;

		AKeyCounter += 250 * Iniko->forceRet * dt;

		if (AKeyCounter >= 500)
		{
			Iniko->forceRet = -1;
		}

		else if (AKeyCounter <= 5)
		{
			Iniko->forceRet = 1;
		}

		Iniko->forceBar->setPosition(Iniko->characterIdleRight->getPosition().x - 85, Iniko->characterIdleRight->getPosition().y + 170);
		Iniko->forceBarBorder->setPosition(Iniko->forceBar->getPosition().x + Iniko->forceBarBorder->getContentSize().width / 2, Iniko->forceBar->getPosition().y + Iniko->forceBarBorder->getContentSize().height / 2);
		Iniko->forceBarBorder->setVisible(true);
		Iniko->forceBar->setVisible(true);
		Iniko->forceBar->setPercentage(AKeyCounter / 5);
	}

	else if (key == ' ' && (contactBody->getTag() / 100) == 20)
	{
		moveCam = false;

		if (AKeyCounter > 0)
		{
			followObject = contactBody->getNode();
			objectsVector.at(contactBody->getTag() - 2000)->getThrow(Iniko->facingRight, AKeyCounter);
			Iniko->forceBarBorder->setVisible(false);
			Iniko->forceBar->setVisible(false);
			Iniko->forceBar->setPercentage(0);
			Iniko->forceRet = 1;
			AKeyCounter = 0;
		}
	}

	else
	{
		Iniko->forceBarBorder->setVisible(false);
		Iniko->forceBar->setVisible(false);
		Iniko->forceBar->setPercentage(0);
		Iniko->forceRet = 1;
		AKeyCounter = 0;
	}

	if (Iniko->hide)
	{
		if (key == 'D')
		{
			Iniko->getHide(false);
			key == ' ';
		}
	}

	/*if (key == '1' && !power1->finish && !power1->activated)
	{
	if (Iniko->facingRight)
	power1->rightDirection = true;

	else
	power1->rightDirection = false;

	power1->activated = true;
	power1->flyParticle->setVisible(true);
	power1->flyParticleSmoke->setVisible(true);
	power1->flyParticleCollider->setEnable(true);
	power1->initialPos = Iniko->characterVision->getPosition().x;
	}

	if (key == '2' && !power2->finish && !power2->activated)
	{
	power2->activated = true;
	//power2->shadowParticle->setVisible(true);

	//Iniko->runningSoundCollider->setEnable(false);
	Iniko->characterIdleRight->setOpacity(128);
	//Iniko->characterIdleRightCollider->setEnable(false);
	Iniko->characterIdleLeft->setOpacity(128);
	//Iniko->characterIdleLeftCollider->setEnable(false);
	Iniko->characterRunningRight->setOpacity(128);
	//Iniko->characterRunningRightCollider->setEnable(false);
	Iniko->characterRunningLeft->setOpacity(128);
	//Iniko->characterRunningLeftCollider->setEnable(false);

	power2->ended(5);
	}*/

	//KEY PRESSED HANDLER

	//CHECK RUNNING SOUND

	if (Iniko->stealth || (!moveRight && !moveLeft) || Iniko->hide || power2->activated || Iniko->jumping)
		Iniko->runningSoundCollider->setEnable(false);

	else
		Iniko->runningSoundCollider->setEnable(true);

	//CHECK RUNNING SOUND

	//FLOOR COLLISION UPDATE

	if (contactFloor != NULL)
	{
		if (Iniko->facingRight)
		{
			if (!Iniko->stealth)
			{
				if ((Iniko->characterIdleRight->getPosition().y - Iniko->characterIdleRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterRunningRight->getPosition().y - Iniko->characterRunningRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterJumpingRight->getPosition().y - Iniko->characterJumpingRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 5))
				{
					Iniko->characterJumpingRight->setPosition(Point(Iniko->characterJumpingRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + 157));
				}

				if ((Iniko->characterIdleLeft->getPosition().y - Iniko->characterIdleLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterRunningLeft->getPosition().y - Iniko->characterRunningLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningLeft->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterJumpingLeft->getPosition().y - Iniko->characterJumpingLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 5))
				{
					Iniko->characterJumpingLeft->setPosition(Point(Iniko->characterJumpingLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + 157));
				}
			}

			else
			{
				if ((Iniko->characterStealthRight->getPosition().y - Iniko->characterStealthRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterStealthRight->setPosition(Point(Iniko->characterStealthRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterIdleRight->getPosition().y - Iniko->characterIdleRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterStealthLeft->getPosition().y - Iniko->characterStealthLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterStealthLeft->setPosition(Point(Iniko->characterStealthLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthLeft->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterIdleLeft->getPosition().y - Iniko->characterIdleLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
				}
			}
		}

		else if (!Iniko->facingRight)
		{
			if (!Iniko->stealth)
			{
				if ((Iniko->characterIdleLeft->getPosition().y - Iniko->characterIdleLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterRunningLeft->getPosition().y - Iniko->characterRunningLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningLeft->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterJumpingLeft->getPosition().y - Iniko->characterJumpingLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 5))
				{
					Iniko->characterJumpingLeft->setPosition(Point(Iniko->characterJumpingLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + 157));
				}

				if ((Iniko->characterIdleRight->getPosition().y - Iniko->characterIdleRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterRunningRight->getPosition().y - Iniko->characterRunningRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterJumpingRight->getPosition().y - Iniko->characterJumpingRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 5))
				{
					Iniko->characterJumpingRight->setPosition(Point(Iniko->characterJumpingRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + 157));
				}
			}

			else
			{
				if ((Iniko->characterStealthRight->getPosition().y - Iniko->characterStealthRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterStealthRight->setPosition(Point(Iniko->characterStealthRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterIdleRight->getPosition().y - Iniko->characterIdleRight->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterStealthLeft->getPosition().y - Iniko->characterStealthLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterStealthLeft->setPosition(Point(Iniko->characterStealthLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthLeft->getContentSize().height / 2 - 5));
				}

				if ((Iniko->characterIdleLeft->getPosition().y - Iniko->characterIdleLeft->getContentSize().height / 2) < (contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 - 10))
				{
					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
				}
			}
		}
	}

	//FLOOR COLLISION UPDATE

	if ((Iniko->gameOver && Iniko->characterJumpingLeft->isVisible()) || (Iniko->gameOver && Iniko->characterJumpingRight->isVisible()))
	{
		Iniko->characterJumpingRight->setVisible(false);
		Iniko->characterJumpingLeft->setVisible(false);
	}

	//COLLISION UPDATE

	switch (contactEnemy->getTag() / 100)
	{
	case 10:														//ENEMY
		if (enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy && !power2->activated && !enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
		{
			enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->stopAllActions();

			if (enemysVector.at(contactEnemy->getTag() - 1000)->facingRight)
			{
				if (Iniko->facingRight)																	//ENEMY KILL BACK RIGHT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 300, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 200);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillBackRightanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 300, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 200);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillBackRightanimation));
					}
				}

				else																					//ENEMY KILL FRONT RIGHT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 100, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillFrontRightanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 100, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillFrontRightanimation));
					}
				}
			}

			else
			{
				if (Iniko->facingRight)																	//ENEMY KILL FRONT LEFT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 150, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillFrontLeftanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 150, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillFrontLeftanimation));
					}
				}

				else																					//ENEMY KILL BACK LEFT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 180, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 190);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillBackLeftanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 180, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 190);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillBackLeftanimation));
					}
				}
			}

			Iniko->die();
			moveRight = false;
			moveLeft = false;
			Iniko->characterVision->runAction(Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(Egipt::gameOver, this)), NULL));
		}

		else if (enemysVector.at(contactEnemy->getTag() - 1000)->facingRight && Iniko->facingRight && !enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy && Iniko->stealth)
		{
			if (Iniko->characterIdleRight->getPosition().x > enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 50 && !enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->returning = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedSound = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy = true;
			}

			else if (key == 'Q' && !Iniko->hide)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->die = true;
				//enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->detect->setVisible(false);

				if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
				{
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1IdleRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1IdleLeftspritebatch->setVisible(false);
				}

				else
				{
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2IdleRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2IdleLeftspritebatch->setVisible(false);
				}

				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 85, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y - 20);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->stopAllActions();
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2DeathRightanimation));
				//enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Sequence::create(DelayTime::create(2.0f), CC_CALLBACK_0(Egipt::enemyDeath, this), NULL));
				//this->runAction(Sequence::create(DelayTime::create(2.0f), CC_CALLBACK_0(Egipt::enemyDeath, this, contactEnemy->getTag() - 1000), NULL));
				moveCam = true;

				Iniko->characterIdleRight->setVisible(false);
				Iniko->characterIdleLeft->setVisible(false);
				Iniko->characterRunningRight->setVisible(false);
				Iniko->characterRunningLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterStealthRight->setVisible(false);
				Iniko->characterStealthLeft->setVisible(false);

				Iniko->characterIdleRight->runAction(Sequence::create(DelayTime::create(1.82), CallFunc::create(CC_CALLBACK_0(Egipt::inikoStopsKill, this)), NULL));
			}
		}

		else if (!enemysVector.at(contactEnemy->getTag() - 1000)->facingRight && !Iniko->facingRight && !enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy && Iniko->stealth)
		{
			if (Iniko->characterIdleLeft->getPosition().x < enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 50 && !enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->returning = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedSound = false;
				enemysVector.at(contactEnemy->getTag() - 1000)->alertedEnemy = true;
			}

			else if (key == 'Q' && !Iniko->hide)
			{
				enemysVector.at(contactEnemy->getTag() - 1000)->die = true;
				//enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(contactEnemy->getTag() - 1000)->detect->setVisible(false);

				if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
				{
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1IdleRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy1IdleLeftspritebatch->setVisible(false);
				}

				else
				{
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2IdleRightspritebatch->setVisible(false);
					enemysVector.at(contactEnemy->getTag() - 1000)->enemy2IdleLeftspritebatch->setVisible(false);
				}

				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 95, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y - 20);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->stopAllActions();
				enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2DeathLeftanimation));
				//enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Sequence::create(DelayTime::create(2.0f), CC_CALLBACK_0(Egipt::enemyDeath, this), NULL));
				//this->runAction(Sequence::create(DelayTime::create(2.0f), CC_CALLBACK_0(Egipt::enemyDeath, this, contactEnemy->getTag() - 1000), NULL));
				moveCam = true;

				Iniko->characterIdleRight->setVisible(false);
				Iniko->characterIdleLeft->setVisible(false);
				Iniko->characterRunningRight->setVisible(false);
				Iniko->characterRunningLeft->setVisible(false);
				Iniko->characterJumpingRight->setVisible(false);
				Iniko->characterJumpingLeft->setVisible(false);
				Iniko->characterStealthRight->setVisible(false);
				Iniko->characterStealthLeft->setVisible(false);

				Iniko->characterIdleRight->runAction(Sequence::create(DelayTime::create(1.82), CallFunc::create(CC_CALLBACK_0(Egipt::inikoStopsKill, this)), NULL));

			}
		}

		else if (!enemysVector.at(contactEnemy->getTag() - 1000)->stunned && !Iniko->stealth && !enemysVector.at(contactEnemy->getTag() - 1000)->die)
		{
			enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->stopAllActions();

			if (enemysVector.at(contactEnemy->getTag() - 1000)->facingRight)
			{
				if (Iniko->facingRight)																	//ENEMY KILL BACK RIGHT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 100, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillFrontRightanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 100, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillFrontRightanimation));
					}
				}

				else																					//ENEMY KILL FRONT RIGHT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 100, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillFrontRightanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x + 100, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillFrontRightanimation));
					}
				}
			}

			else
			{
				if (Iniko->facingRight)																	//ENEMY KILL FRONT LEFT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 150, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillFrontLeftanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 150, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillFrontLeftanimation));
					}
				}

				else																					//ENEMY KILL BACK LEFT
				{
					if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy1RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 150, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1KillFrontLeftanimation));
					}

					else if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 2)
					{
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2WalkingLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningRightspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemy2RunningLeftspritebatch->setVisible(false);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setPosition(enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().x - 150, enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->getPosition().y + 50);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->setVisible(true);
						enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2KillFrontLeftanimation));
					}
				}
			}

			Iniko->die();
			moveRight = false;
			moveLeft = false;
			Iniko->characterVision->runAction(Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(Egipt::gameOver, this)), NULL));
		}

		break;
	}

	switch (contactBody->getTag() / 100)
	{
	case 20:														//THROWABLE OBJECT
																	/*if (key == ' ' && AKeyCounter > 0)
																	{
																	followObject = contactBody->getNode();
																	objectsVector.at(contactBody->getTag() - 2000)->getThrow(Iniko->facingRight, AKeyCounter);
																	}*/
		break;

	case 30:														//OBJECTO TO HIDE
		if (key == 'U')
		{
			if (!Iniko->hide)
				Iniko->getHide(true);
		}
		break;

	}

	//COLLISION UPDATE

	//CAMERA FOLLOW AND ZOOM OUT UPDATE

	if (followObject != NULL)
	{
		Point screenCenter = Point(visibleSize.width / 2, visibleSize.height / 2);
		Point offSetToCenter = ccpSub(screenCenter, followObject->getPosition());

		this->setPosition(ccpMult(offSetToCenter, this->getScale()));
		this->setPositionY(this->getPositionY() - offSetToCenter.y - (followObject->getPosition().y - (313 / 2 + Floor1->getContentSize().height)) + 200);
	}

	else if (followObject == NULL)
	{
		Point screenCenter = Point(visibleSize.width / 2, visibleSize.height / 2);
		//Point offSetToCenter = ccpSub(screenCenter, Iniko->characterIdleRight->getPosition());
		Point offSetToCenter = ccpSub(screenCenter, Iniko->characterRunningRight->getPosition());

		this->setPosition(ccpMult(offSetToCenter, this->getScale()));
		this->setPositionY(this->getPositionY() - offSetToCenter.y - (Iniko->characterRunningRight->getPosition().y - (313 / 2 + Floor1->getContentSize().height)) + 200);
	}

	//CAMERA FOLLOW AND ZOOM OUT UPDATE

	//OBJECT POSITION UPDATE WHEN THROW

	if (followObject != NULL)
	{
		//objectsVector.at(followObject->getTag() - 2000)->itemSound->setPosition(objectsVector.at(followObject->getTag() - 2000)->itemArt->getPosition());
		moveCam = true;
	}

	//OBJECT POSITION UPDATE WHEN THROW
}

void Egipt::setPhysicsWorld(PhysicsWorld *world)
{
	mWorld = world;
	mWorld->setGravity(Vec2(0, -1000));
}

bool Egipt::onContactBegin(PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag() / 100 == 90)										//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 30:													//..AN OBJECT TO HIDE
			contactBody = bodyB;
			break;

		case 10:													//..AN ENEMY
			if (!enemysVector.at(bodyB->getTag() - 1000)->die)
				contactEnemy = bodyB;
			break;

		case 20:													//..A THROWABLE OBJECT
			contactBody = bodyB;
			Iniko->AKey->setVisible(true);
			break;

		case 40:													//..A JUMP ZONE
			contactBody = bodyB;
			break;
		}
	}

	if (bodyB->getTag() / 100 == 90)										//IF CHARACTER COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 30:													//..AN OBJECT TO HIDE
			contactBody = bodyA;
			break;

		case 10:													//..AN ENEMY
			if (!enemysVector.at(bodyA->getTag() - 1000)->die)
				contactEnemy = bodyA;
			break;

		case 20:													//..A THROWABLE OBJECT
			contactBody = bodyA;
			Iniko->AKey->setVisible(true);
			break;

		case 40:													//..A JUMP ZONE
			contactBody = bodyA;
			break;
		}
	}

	if (bodyA->getTag() / 100 == 11)									//IF ENEMY VISION COLLIDES WITH..
	{
		if (!enemysVector.at(bodyA->getTag() - 1100)->die && !enemysVector.at(bodyA->getTag() - 1100)->stunned)
		{
			switch (bodyB->getTag() / 100)
			{
			case 90:												//..CHARACTER
				if (!power2->activated)
				{
					enemysVector.at(bodyA->getTag() - 1100)->returning = false;
					enemysVector.at(bodyA->getTag() - 1100)->alertedSound = false;
					enemysVector.at(bodyA->getTag() - 1100)->alertedEnemy = true;
				}
				break;
			}
		}
	}

	if (bodyB->getTag() / 100 == 11)									//IF ENEMY VISION COLLIDES WITH..
	{
		if (!enemysVector.at(bodyB->getTag() - 1100)->die && !enemysVector.at(bodyB->getTag() - 1100)->stunned)
		{
			switch (bodyA->getTag() / 100)
			{
			case 90:												//..CHARACTER
				if (!power2->activated)
				{
					enemysVector.at(bodyB->getTag() - 1100)->returning = false;
					enemysVector.at(bodyB->getTag() - 1100)->alertedSound = false;
					enemysVector.at(bodyB->getTag() - 1100)->alertedEnemy = true;
				}
				break;
			}
		}
	}

	if (bodyA->getTag() / 100 == 10)									//IF ENEMY COLLIDES WITH..
	{
		if (!enemysVector.at(bodyA->getTag() - 1000)->die && !enemysVector.at(bodyA->getTag() - 1000)->stunned)
		{
			switch (bodyB->getTag() / 100)
			{
			case 91:												//..CHARACTER RUNNING SOUND
				if (!Iniko->stealth && !power2->activated)
				{
					enemysVector.at(bodyA->getTag() - 1000)->alertedSound = true;
					enemysVector.at(bodyA->getTag() - 1000)->followPos = Iniko->characterIdleRight->getPosition().x;
				}
				break;

			case 21:												//..ITEM SOUND
				enemysVector.at(bodyA->getTag() - 1000)->alertedSound = true;
				enemysVector.at(bodyA->getTag() - 1000)->followPos = objectsVector.at(bodyB->getTag() - 2100)->itemArt->getPosition().x;
				break;

			case 41:												//..FLY POWER
				enemysVector.at(bodyA->getTag() - 1000)->stunned = true;
				enemysVector.at(bodyA->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(bodyA->getTag() - 1000)->detect->setVisible(false);
				//power1->flyParticle->setPosition(enemysVector.at(bodyA->getTag() - 1000)->getPosition());
				power1->flyParticleCollider->setEnable(false);
				power1->ended(3);
				enemysVector.at(bodyA->getTag() - 1000)->recovery();
				break;
			}
		}
	}

	if (bodyB->getTag() / 100 == 10)									//IF ENEMY COLLIDES WITH..
	{
		if (!enemysVector.at(bodyB->getTag() - 1000)->die && !enemysVector.at(bodyB->getTag() - 1000)->stunned)
		{
			switch (bodyA->getTag() / 100)
			{
			case 91:												//..CHARACTER RUNNING SOUND
				if (!Iniko->stealth && !power2->activated)
				{
					enemysVector.at(bodyB->getTag() - 1000)->alertedSound = true;
					enemysVector.at(bodyB->getTag() - 1000)->followPos = Iniko->characterIdleRight->getPosition().x;
				}
				break;

			case 21:												//..ITEM SOUND
				enemysVector.at(bodyB->getTag() - 1000)->alertedSound = true;
				enemysVector.at(bodyB->getTag() - 1000)->followPos = objectsVector.at(bodyA->getTag() - 2100)->itemArt->getPosition().x;
				break;

			case 41:												//..FLY POWER
				enemysVector.at(bodyB->getTag() - 1000)->stunned = true;
				enemysVector.at(bodyB->getTag() - 1000)->enemyVision->setVisible(false);
				enemysVector.at(bodyB->getTag() - 1000)->detect->setVisible(false);
				//power1->flyParticle->setPosition(enemysVector.at(bodyB->getTag() - 1000)->getPosition());
				power1->flyParticleCollider->setEnable(false);
				power1->ended(3);
				enemysVector.at(bodyB->getTag() - 1000)->recovery();
				break;
			}
		}
	}

	if (bodyB->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyA->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyA->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyA, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyA, 2)), NULL));
			}

			break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		if (bodyA->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			if (Iniko->characterJumpingRightCollider->getVelocity().y < 0 || Iniko->characterJumpingLeftCollider->getVelocity().y < 0)
			{
				if (((Iniko->characterJumpingRight->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)) || ((Iniko->characterJumpingLeft->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)))
				{
					Iniko->jumping = false;
					Iniko->stealth = false;

					Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterStealthRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterStealthLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));

					//bodyA->setVelocity(Vec2::ZERO);
					Iniko->characterJumpingRightCollider->setGravityEnable(false);
					Iniko->characterJumpingLeftCollider->setGravityEnable(false);
					Iniko->characterRunningRightCollider->setGravityEnable(false);
					Iniko->characterRunningLeftCollider->setGravityEnable(false);
					Iniko->characterIdleRightCollider->setGravityEnable(false);
					Iniko->characterIdleLeftCollider->setGravityEnable(false);
					Iniko->characterStealthRightCollider->setGravityEnable(false);
					Iniko->characterStealthLeftCollider->setGravityEnable(false);

					/*Iniko->characterJumpingRightCollider->setGravityEnable(false);
					Iniko->characterJumpingLeftCollider->setGravityEnable(false);
					Iniko->characterRunningRightCollider->setGravityEnable(false);
					Iniko->characterRunningLeftCollider->setGravityEnable(false);
					Iniko->characterIdleRightCollider->setGravityEnable(false);
					Iniko->characterIdleLeftCollider->setGravityEnable(false);*/

					contactFloor = bodyB;

					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
					Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningLeft->getContentSize().height / 2 - 5));
					Iniko->characterJumpingLeft->setPosition(Point(Iniko->characterJumpingLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingLeft->getContentSize().height / 2 - 5));
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
					Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningRight->getContentSize().height / 2 - 5));
					Iniko->characterJumpingRight->setPosition(Point(Iniko->characterJumpingRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingRight->getContentSize().height / 2 - 5));
					Iniko->characterStealthRight->setPosition(Point(Iniko->characterStealthRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthRight->getContentSize().height / 2 - 5));
					Iniko->characterStealthLeft->setPosition(Point(Iniko->characterStealthLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthLeft->getContentSize().height / 2 - 5));
				}
			}

			//}

			//moveCam = false;
		}

		else
		{
			bodyA->setVelocity(Vec2::ZERO);
			bodyA->setGravityEnable(false);
		}
	}

	if (bodyA->getTag() == -1)											//IF FLOOR COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyB->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyB->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyB, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyB, 2)), NULL));

			}

			break;
		}

		//DEFAULT ACTIONS TO EVERYONE

		if (bodyB->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			if (Iniko->characterJumpingRightCollider->getVelocity().y < 0 || Iniko->characterJumpingRightCollider->getVelocity().y < 0)
			{
				if (((Iniko->characterJumpingRight->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)) || ((Iniko->characterJumpingLeft->getPosition().y) >(bodyB->getNode()->getPosition().y + bodyB->getNode()->getContentSize().height / 2)))
				{
					Iniko->jumping = false;
					Iniko->stealth = false;

					Iniko->characterJumpingRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterJumpingLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterRunningLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterIdleLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterStealthRightCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));
					Iniko->characterStealthLeftCollider->setVelocity(Vec2(Iniko->characterJumpingRightCollider->getVelocity().x, 0));

					//bodyA->setVelocity(Vec2::ZERO);

					Iniko->characterJumpingRightCollider->setGravityEnable(false);
					Iniko->characterJumpingLeftCollider->setGravityEnable(false);
					Iniko->characterRunningRightCollider->setGravityEnable(false);
					Iniko->characterRunningLeftCollider->setGravityEnable(false);
					Iniko->characterIdleRightCollider->setGravityEnable(false);
					Iniko->characterIdleLeftCollider->setGravityEnable(false);
					Iniko->characterStealthRightCollider->setGravityEnable(false);
					Iniko->characterStealthLeftCollider->setGravityEnable(false);

					//bodyB->setVelocity(Vec2::ZERO);
					//bodyB->setGravityEnable(false);

					contactFloor = bodyA;

					Iniko->characterIdleLeft->setPosition(Point(Iniko->characterIdleLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleLeft->getContentSize().height / 2 - 5));
					Iniko->characterRunningLeft->setPosition(Point(Iniko->characterRunningLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningLeft->getContentSize().height / 2 - 5));
					Iniko->characterJumpingLeft->setPosition(Point(Iniko->characterJumpingLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingLeft->getContentSize().height / 2 - 5));
					Iniko->characterIdleRight->setPosition(Point(Iniko->characterIdleRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterIdleRight->getContentSize().height / 2 - 5));
					Iniko->characterRunningRight->setPosition(Point(Iniko->characterRunningRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterRunningRight->getContentSize().height / 2 - 5));
					Iniko->characterJumpingRight->setPosition(Point(Iniko->characterJumpingRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterJumpingRight->getContentSize().height / 2 - 5));
					Iniko->characterStealthRight->setPosition(Point(Iniko->characterStealthRight->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthRight->getContentSize().height / 2 - 5));
					Iniko->characterStealthLeft->setPosition(Point(Iniko->characterStealthLeft->getPosition().x, contactFloor->getNode()->getPosition().y + contactFloor->getNode()->getContentSize().height / 2 + Iniko->characterStealthLeft->getContentSize().height / 2 - 5));
				}
			}

			//}

			//moveCam = false;
		}

		else
		{
			bodyB->setVelocity(Vec2::ZERO);
			bodyB->setGravityEnable(false);
		}
	}

	if (bodyB->getTag() == -2)											//IF WALL COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = bodyB->getNode();
			break;

		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyA->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyA->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyA, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyA, 2)), NULL));
			}

			break;
		}
	}

	if (bodyA->getTag() == -2)											//IF WALL COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = bodyA->getNode();
			break;

		case 20:													//..AN OBJECT
			if (objectsVector.at(bodyB->getTag() - 2000)->thrown)
			{
				objectsVector.at(bodyB->getTag() - 2000)->itemArt->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyB, 1)), DelayTime::create(0.1), CallFunc::create(CC_CALLBACK_0(Egipt::objectBehaviour, this, bodyB, 2)), NULL));
			}

			break;
		}
	}

	if (bodyB->getTag() == -3)											//IF ENEMY WALL COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 10:													//ENEMY
			enemysVector.at(bodyA->getTag() - 1000)->alertedEnemy = false;
			enemysVector.at(bodyA->getTag() - 1000)->alertedSound = false;
			enemysVector.at(bodyA->getTag() - 1000)->returning = true;
			break;
		}
	}

	if (bodyA->getTag() == -3)											//IF ENEMY WALL COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 10:													//ENEMY
			enemysVector.at(bodyB->getTag() - 1000)->alertedEnemy = false;
			enemysVector.at(bodyB->getTag() - 1000)->alertedSound = false;
			enemysVector.at(bodyB->getTag() - 1000)->returning = true;
			break;
		}
	}

	return true;
}

bool Egipt::onContactSeparate(PhysicsContact &contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getTag() / 100 == 90)										//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 10:													//..AN ENEMY
			contactEnemy = PhysicsBody::create();
			contactEnemy->setTag(9999);
			break;

		case 40:													//..A JUMP ZONE
			Iniko->SKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 30:													//..AN OBJECT TO HIDE
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 20:													//..A THROWABLE OBJECT
			Iniko->AKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;
		}
	}

	if (bodyB->getTag() / 100 == 90)										//IF CHARACTER STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 10:													//..AN ENEMY
			contactEnemy = PhysicsBody::create();
			contactEnemy->setTag(9999);
			break;

		case 40:													//..A JUMP ZONE
			Iniko->SKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 30:													//..AN OBJECT TO HIDE
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;

		case 20:													//..A THROWABLE OBJECT
			Iniko->AKey->setVisible(false);
			contactBody = PhysicsBody::create();
			contactBody->setTag(9999);
			break;
		}
	}

	if (bodyA->getTag() / 100 == 10)									//IF ENEMY STOPS TO COLLIDE WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 91:													//CHARACTER RUNNING SOUND
																	//enemysVector.at(bodyA->getTag() - 1000)->alertedSound = false;
			break;
		}
	}

	if (bodyB->getTag() / 100 == 10)									//IF ENEMY STOPS TO COLLIDE WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 91:													//CHARACTER RUNNING SOUND
																	//enemysVector.at(bodyB->getTag() - 1000)->alertedSound = false;
			break;
		}
	}

	if (bodyA->getTag() / 100 == 11)									//IF ENEMY VISION STOPS TO COLLIDE WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 90:													//CHARACTER
			enemysVector.at(bodyA->getTag() - 1100)->alertedEnemy = false;
			enemysVector.at(bodyA->getTag() - 1100)->alertedSound = true;
			enemysVector.at(bodyA->getTag() - 1100)->followPos = Iniko->characterIdleRight->getPosition().x;
			break;
		}
	}

	if (bodyB->getTag() / 100 == 11)									//IF ENEMY VISION STOPS TO COLLIDE WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 90:													//CHARACTER
			enemysVector.at(bodyB->getTag() - 1100)->alertedEnemy = false;
			enemysVector.at(bodyB->getTag() - 1100)->alertedSound = true;
			enemysVector.at(bodyB->getTag() - 1100)->followPos = Iniko->characterIdleRight->getPosition().x;
			break;
		}
	}

	if (bodyB->getTag() == -2)											//IF WALL STOPS TO COLLIDES WITH..
	{
		switch (bodyA->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = NULL;
			Iniko->wallTouchSide = ' ';
			break;
		}
	}

	if (bodyA->getTag() == -2)											//IF WALL STOPS TO COLLIDES WITH..
	{
		switch (bodyB->getTag() / 100)
		{
		case 90:													//CHARACTER
			Iniko->wallTouch = NULL;
			Iniko->wallTouchSide = ' ';
			break;
		}
	}

	if (bodyB->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		if (bodyA->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			//bodyA->setVelocity(Vec2::ZERO);
			//bodyA->setGravityEnable(false);

			Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setGravityEnable(true);
			Iniko->characterStealthRightCollider->setGravityEnable(true);
			Iniko->characterStealthLeftCollider->setGravityEnable(true);

			//contactFloor = bodyB;
			//}

			//moveCam = false;
			contactFloor = NULL;
		}

		//bodyA->setGravityEnable(true);
		//contactFloor = NULL;
	}

	if (bodyA->getTag() == -1)											//IF FLOOR STOPS TO COLLIDES WITH..
	{
		if (bodyB->getTag() / 100 == 90)
		{
			//if (!Iniko->jumping)
			//{
			/*if ((Iniko->characterIdleRightCollider->getVelocity().y < 0) && (Iniko->characterIdleLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			/*if ((Iniko->characterRunningRightCollider->getVelocity().y < 0) && (Iniko->characterRunningLeftCollider->getVelocity().y < 0))
			{
			moveCam = false;
			}*/

			//bodyA->setVelocity(Vec2::ZERO);
			//bodyA->setGravityEnable(false);

			Iniko->characterJumpingRightCollider->setGravityEnable(true);
			Iniko->characterJumpingLeftCollider->setGravityEnable(true);
			Iniko->characterRunningRightCollider->setGravityEnable(true);
			Iniko->characterRunningLeftCollider->setGravityEnable(true);
			Iniko->characterIdleRightCollider->setGravityEnable(true);
			Iniko->characterIdleLeftCollider->setGravityEnable(true);
			Iniko->characterStealthRightCollider->setGravityEnable(true);
			Iniko->characterStealthLeftCollider->setGravityEnable(true);

			//contactFloor = bodyB;
			//}

			//moveCam = false;
			contactFloor = NULL;
		}

		//bodyB->setGravityEnable(true);
		//contactFloor = NULL;
	}

	return true;
}

void Egipt::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	_pressedKey = keyCode;

	if (!Iniko->gameOver)
	{
		switch (_pressedKey)
		{
			/*case EventKeyboard::KeyCode::KEY_SPACE:
			if (followObject == NULL && !Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
			this->setScale(0.5);

			moveCam = true;
			}
			break;*/

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			moveRight = true;
			break;

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			moveLeft = true;
			break;

		case EventKeyboard::KeyCode::KEY_TAB:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
				Iniko->stealth = true;
			break;

		case EventKeyboard::KeyCode::KEY_W:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
				key = 'W';
			break;

		case EventKeyboard::KeyCode::KEY_SPACE:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'S';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egipt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_Q:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'Q';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egipt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'U';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egipt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0))
			{
				key = 'D';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egipt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_1:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0) && !Iniko->hide)
			{
				key = '1';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egipt::keyNull, this)), NULL));
			}
			break;

		case EventKeyboard::KeyCode::KEY_2:
			if (!Iniko->jumping && (Iniko->characterJumpingRightCollider->getVelocity().y >= 0) && (Iniko->characterJumpingLeftCollider->getVelocity().y >= 0) && !Iniko->hide)
			{
				key = '2';
				this->runAction(Sequence::create(DelayTime::create(0.001f), CallFunc::create(CC_CALLBACK_0(Egipt::keyNull, this)), NULL));
			}
			break;
		}
	}
}

void Egipt::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		moveRight = false;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		moveLeft = false;
		break;

		/*case EventKeyboard::KeyCode::KEY_SPACE:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		if (this->getScale() == 0.5)
		{
		this->setScale(0.7);

		moveCam = false;
		}
		break;*/

	case EventKeyboard::KeyCode::KEY_TAB:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		Iniko->stealth = false;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_Q:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_1:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;

	case EventKeyboard::KeyCode::KEY_2:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		key = ' ';
		break;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		_pressedKey = EventKeyboard::KeyCode::KEY_NONE;
		AKeyCounter += 300;
		if (AKeyCounter > 800)
			AKeyCounter = 800;
		key = ' ';
		break;
	}
}

void Egipt::createAnimations()
{
	//PORTAL PARTICLES

	portalParticles = CCParticleSystemQuad::create("Particles/PortalParticles/portal_particle.plist");
	portalParticles->setScale(0.4);
	portalParticles->setPosition(Point(0, 338));
	portalParticles->setPositionType(kCCPositionTypeRelative);
	addChild(portalParticles, 5);

	//FIRE PARTICLES

	fireParticle1 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle1->setScale(0.8);
	fireParticle1->setPosition(Point(13469, 300));
	fireParticle1->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle1, 5);

	fireParticle2 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle2->setScale(0.8);
	fireParticle2->setPosition(Point(14760, 300));
	fireParticle2->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle2, 5);

	fireParticle3 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle3->setScale(0.8);
	fireParticle3->setPosition(Point(17835, 300));
	fireParticle3->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle3, 5);

	fireParticle4 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle4->setScale(0.8);
	fireParticle4->setPosition(Point(22055, 300));
	fireParticle4->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle4, 5);

	fireParticle5 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle5->setScale(0.8);
	fireParticle5->setPosition(Point(24025, 300));
	fireParticle5->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle5, 5);

	fireParticle6 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle6->setScale(0.8);
	fireParticle6->setPosition(Point(25130, 300));
	fireParticle6->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle6, 5);

	fireParticle7 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle7->setScale(0.8);
	fireParticle7->setPosition(Point(27649, 300));
	fireParticle7->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle7, 5);

	fireParticle8 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle8->setScale(0.8);
	fireParticle8->setPosition(Point(28930, 300));
	fireParticle8->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle8, 5);

	fireParticle9 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle9->setScale(0.8);
	fireParticle9->setPosition(Point(30722, 300));
	fireParticle9->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle9, 5);

	fireParticle10 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle10->setScale(0.8);
	fireParticle10->setPosition(Point(32224, 300));
	fireParticle10->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle10, 5);

	fireParticle11 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle11->setScale(0.8);
	fireParticle11->setPosition(Point(35868, 300));
	fireParticle11->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle11, 5);

	fireParticle12 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle12->setScale(0.8);
	fireParticle12->setPosition(Point(36822, 300));
	fireParticle12->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle12, 5);

	fireParticle13 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle13->setScale(0.8);
	fireParticle13->setPosition(Point(37452, 300));
	fireParticle13->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle13, 5);

	fireParticle14 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle14->setScale(0.8);
	fireParticle14->setPosition(Point(38196, 300));
	fireParticle14->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle14, 5);

	fireParticle15 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle15->setScale(0.8);
	fireParticle15->setPosition(Point(38196, 300));
	fireParticle15->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle15, 5);

	fireParticle16 = CCParticleSystemQuad::create("Particles/FireParticle/fire_particle.plist");
	fireParticle16->setScale(0.8);
	fireParticle16->setPosition(Point(38196, 300));
	fireParticle16->setPositionType(kCCPositionTypeRelative);
	addChild(fireParticle16, 5);
}

void Egipt::keyNull()
{
	key = ' ';
}

void Egipt::objectBehaviour(PhysicsBody* body, int phase)
{
	if (phase == 1)
	{
		objectsVector.at(body->getTag() - 2000)->itemSoundCollider->setEnable(true);
	}

	else
	{
		objectsVector.at(body->getTag() - 2000)->itemSoundCollider->setEnable(false);
		objectsVector.at(body->getTag() - 2000)->itemArt->setVisible(false);
		objectsVector.at(body->getTag() - 2000)->itemCollider->setEnable(false);
		objectsVector.at(body->getTag() - 2000)->itemArt->stopAllActions();
		//removeChild(objectsVector.at(body->getTag() - 2000)->itemArt);
		followObject = NULL;
		moveCam = false;
	}
}

void Egipt::gameOver()
{
	auto scene = GameOver::createScene();
	scene->setTag(10 + Iniko->checkpoint);

	Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}

void Egipt::enemyDeath(int tg)
{
	enemysVector.at(tg)->die = true;
}

void Egipt::inikoStopsKill()
{
	moveCam = false;

	Iniko->getHide(false);

	//if(Iniko->facingRight)
	//Iniko->characterIdleRight->setVisible(true);
}

void Egipt::enemyDying()
{
	if (enemysVector.at(contactEnemy->getTag() - 1000)->type == 1)
	{
		if (enemysVector.at(contactEnemy->getTag() - 1000)->facingRight)
			enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1DeathLeftanimation));

		else
			enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy1DeathRightanimation));
	}

	else
	{
		if (enemysVector.at(contactEnemy->getTag() - 1000)->facingRight)
			enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2DeathLeftanimation));

		else
			enemysVector.at(contactEnemy->getTag() - 1000)->enemyArt->runAction(Animate::create(enemysVector.at(contactEnemy->getTag() - 1000)->enemy2DeathRightanimation));
	}
}