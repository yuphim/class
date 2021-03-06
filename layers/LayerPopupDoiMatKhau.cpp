//
//  LayerPopupDoiMatKhau.cpp
//  iCasino_v4
//
//  Created by Sherlock Tuan on 7/19/17.
//
//

#include "LayerPopupDoiMatKhau.h"
//
//  LayerPopupDoiMatKhau.cpp
//  iCasino_v4
//
//  Created by Sherlock Tuan on 6/24/17.
//
//

#include "LayerPopupDoiMatKhau.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../layergames/ChanUtils.h"
#include "../Common.h"
#include "../SceneManager.h"
#include "../mUtils.h"
#include "../layergames/PhomMessDef.h"
#include "LayerPopupThongBao.h"
#include "../data_manager.h"
#include "../layergames/_Chat_.h"
#include "LayerPopupOTP.h"
#include "Util/PasswordUtil.h"
#include "../scenes/SceneMain.h"
LayerPopupDoiMatKhau::LayerPopupDoiMatKhau()
{
    GameServer::getSingleton().addListeners(this);
}


LayerPopupDoiMatKhau::~LayerPopupDoiMatKhau()
{
    GameServer::getSingleton().removeListeners(this);
    
}

bool LayerPopupDoiMatKhau::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    
    auto rootNode = CSLoader::getInstance()->createNode("LayerPopupDoiMatKhau.csb");
    auto Panel_2 = static_cast<Layout*>(rootNode->getChildByName("Panel_2"));
    Panel_2->setScale(visibleSize.height / DESIGN_RESOLUTION_HEIGHT);
        rootNode->setAnchorPoint(Point(0.5, 0.5));
        rootNode->setPosition(Point(visibleSize / 2));
        Size sizeAdd;
    //    if (SceneManager::getSingleton().getGameID() != kGameChan && SceneManager::getSingleton().getGameID() != kGameXiTo){
            sizeAdd = ChanUtils::getSizePos();
//
//        }else{
//            sizeAdd = Size(0,0);
//        }
        Size sizeAdd2 = Size(0,0);
        rootNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2-sizeAdd2.height));
    
    ui::Helper::doLayout(rootNode);
    
    this->addChild(rootNode);
    
    auto pnlBg = static_cast<Layout*>(rootNode->getChildByName("pnlBg"));
    //pnlBg->setPosition(Point(visibleSize.width/2,visibleSize.height/2- sizeAdd2.height));
    Button* btnClose = dynamic_cast<Button*>(pnlBg->getChildByName("btnClose"));
    if(btnClose){
        btnClose->addClickEventListener(CC_CALLBACK_1(LayerPopupDoiMatKhau::onBtnClose, this));
    }
    
    auto lblTitle = static_cast<Text*> (pnlBg->getChildByName("Text_1"));
    lblTitle->setString(dataManager.GetSysString(779));
    this->txtOldPass = static_cast<TextField*>(pnlBg->getChildByName("txtOldPass"));
    this->txtOldPass->setPlaceHolder(dataManager.GetSysString(843));
    this->txtmatkhauMoi = static_cast<TextField*>(pnlBg->getChildByName("txtNewPass"));
    this->txtmatkhauMoi->setPlaceHolder(dataManager.GetSysString(844));

    this->txtnhaplaiMatKhauMoi = static_cast<TextField*>(pnlBg->getChildByName("txtNewRePass"));
    this->txtnhaplaiMatKhauMoi->setPlaceHolder(dataManager.GetSysString(845));

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    this->txtOldPass->setMaxLength(20);
    this->txtmatkhauMoi->setMaxLength(20);

    this->txtnhaplaiMatKhauMoi->setMaxLength(20);

#endif
    Button* btnCapNhat = dynamic_cast<Button*>(pnlBg->getChildByName("btnCapNhat"));
    if(btnCapNhat){
        btnCapNhat->addClickEventListener(CC_CALLBACK_1(LayerPopupDoiMatKhau::onBtnCapNhat, this));
        btnCapNhat->setTitleText(dataManager.GetSysString(786));
    }
    
    this->lblError = static_cast<Text*>(pnlBg->getChildByName("txtError"));
    
    boost::shared_ptr<ISFSObject> params(new SFSObject());
    params->PutUtfString("aI", SceneManager::getSingleton().getMyName());
    boost::shared_ptr<IRequest> request(new ExtensionRequest("rgaci", params));
    GameServer::getSingleton().Send(request);

    
    SceneManager::getSingleton().showLoading();
    this->setScale(1);
    return true;
}
void LayerPopupDoiMatKhau::onBtnOTP(Ref* pSender){
    LayerPopupOTP* otp = LayerPopupOTP::create();
    this->addChild(otp);
}
void LayerPopupDoiMatKhau::onBtnCapNhat(Ref* pSender){
       // log("onButtonUpdate");
    
        std::string strNewPass = string(txtmatkhauMoi->getString());
        for (int i = 0; i < strNewPass.size(); ++i)
        {
            if (strNewPass.at(i) == ' '){
                lblError->setVisible(true);
                lblError->setString(dataManager.GetSysString(468));
                return;
            }
        }
        string _oldPass_ = txtOldPass->getString();
        boost::shared_ptr<string> _pass = PasswordUtil::MD5Password(_oldPass_);
        _pass = PasswordUtil::MD5Password(*_pass);
    
    if (SceneManager::getSingleton().isNagaCard){
        _pass = PasswordUtil::MD5Password(_oldPass_+SceneManager::getSingleton().getMyName());
        _pass = PasswordUtil::MD5Password(*_pass);
    }
    
        if (strcmp(_oldPass.c_str(), "") == 0){
    
        }
        else{
    
            if (_pass->compare(_oldPass) != 0){
                //this->showToast("Mật khẩu cũ không đúng!");
                lblError->setVisible(true);
                lblError->setString(dataManager.GetSysString(621));
                return;
            }
            else{
                lblError->setVisible(false);
            }
    
        }
    
        //Validate
        int len1 = (txtOldPass->getString().length());
        int len2 = (txtmatkhauMoi->getString().length());
        int len3 = (txtnhaplaiMatKhauMoi->getString().length());
    
        if (txtmatkhauMoi->getString().compare(txtnhaplaiMatKhauMoi->getString()) != 0){
            lblError->setVisible(true);
            lblError->setString(dataManager.GetSysString(467));
            return;
        }
        else{
            lblError->setVisible(false);
        }
        if (len2 < 6 || len2 >24 || len3 < 6 || len3 >24){
            lblError->setVisible(true);
            lblError->setString(dataManager.GetSysString(466));
            return;
        }
        else{
            lblError->setVisible(false);
        }
        if (strcmp(_name.c_str(), txtmatkhauMoi->getString().c_str()) == 0){
            lblError->setString(dataManager.GetSysString(698));
            lblError->setVisible(true);
            return;
        }
        else{
            lblError->setVisible(false);
        }
        if (mUtils::isNumber(txtmatkhauMoi->getString().c_str())){
            lblError->setVisible(true);
            lblError->setString(dataManager.GetSysString(471));
            return;
        }
        else{
            lblError->setVisible(false);
        }
        if (!mUtils::checkAlpha(txtmatkhauMoi->getString().c_str())){
            lblError->setVisible(true);
            lblError->setString(dataManager.GetSysString(471));
            return;
        }
        else{
            lblError->setVisible(false);
        }
        if (strcmp(_oldPass_.c_str(), txtmatkhauMoi->getString().c_str()) == 0){
            lblError->setVisible(true);
            lblError->setString(dataManager.GetSysString(622));
    
            return;
        }
        else{
            lblError->setVisible(false);
        }
    
        //Send request
        boost::shared_ptr<User> myself = GameServer::getSingleton().getSmartFox()->MySelf();
        if (myself == NULL)
            return;
        //Send request
        boost::shared_ptr<ISFSObject> params(new SFSObject());
        params->PutUtfString("aI", myself->Name());
    
        params->PutUtfString("aP", _pass);
    
    
        //md5
        boost::shared_ptr<string> _npass = PasswordUtil::MD5Password(txtmatkhauMoi->getString());
        _npass = PasswordUtil::MD5Password(*_npass);
    
    if (SceneManager::getSingleton().isNagaCard){
        _npass = PasswordUtil::MD5Password(txtmatkhauMoi->getString()+SceneManager::getSingleton().getMyName());
        _npass = PasswordUtil::MD5Password(*_npass);
    }
    
        params->PutUtfString("aNP", _npass);
    
        boost::shared_ptr<IRequest> request(new ExtensionRequest("rcp", params)); //Change password
        GameServer::getSingleton().Send(request);
}

void LayerPopupDoiMatKhau::onBtnClose(Ref* pSender){
    this->removeFromParentAndCleanup(true);
}

void LayerPopupDoiMatKhau::OnExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEvetnParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEvetnParams)["cmd"];
    boost::shared_ptr<string> cmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
    
    boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEvetnParams)["params"];
    boost::shared_ptr<ISFSObject> param = ((boost::static_pointer_cast<ISFSObject>(ptrEventParamValueParams)));
    
     if (strcmp("cpc", cmd->c_str()) == 0){
       // log("change pass rc: %ld", *param->GetInt("rc"));
        
        if (*param->GetInt("rc") == 0){//OK
           // log("lbfree OK");
            SceneManager::getSingleton().showToast(dataManager.GetSysString(148));
            this->txtOldPass->setString("");
            this->txtmatkhauMoi->setString("");
            this->txtnhaplaiMatKhauMoi->setString("");
            
        }
        else{//Not OK
           // log("lbfree Not OK - error: %s", param->GetUtfString("rd")->c_str());
            SceneManager::getSingleton().showToast(*param->GetUtfString("rd"));
        }
    }
    else if (strcmp("gaic", cmd->c_str()) == 0){
        SceneManager::getSingleton().hideLoading();
                if (param->GetUtfString("aP") != NULL && param->GetUtfString("aM") != NULL){
        //Insert datas to textfield
                    _oldPass = *param->GetUtfString("aP");
                }
        //this->runAction(Sequence::create(ScaleTo::create(0.2, 1.1),ScaleTo::create(0.2, 1),NULL));

    }
}
void LayerPopupDoiMatKhau::OnSmartFoxUserVariableUpdate(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
    boost::shared_ptr<map<string, boost::shared_ptr<void> > > ptrEventParams = ptrEvent->Params();
    boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
    boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
    
   }

bool LayerPopupDoiMatKhau::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    return true;
}

void LayerPopupDoiMatKhau::onEnter()
{
    Layer::onEnter();
    SceneManager::getSingleton().numPopup+=1;

    //    auto dispatcher = Director::getInstance()->getEventDispatcher();
    //    auto listener = EventListenerTouchOneByOne::create();
    //    listener->setSwallowTouches(true);
    //    listener->onTouchBegan = CC_CALLBACK_2(LayerPopupDoiMatKhau::onTouchBegan, this);
    //    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //    _touchListener = listener;
    //
    //    GameServer::getSingleton().addListeners(this);
}

void LayerPopupDoiMatKhau::onExit()
{
    Layer::onExit();
    SceneManager::getSingleton().numPopup-=1;
   // SceneMain::getSingleton().gotoDiemDanh();
    //    auto dispatcher = Director::getInstance()->getEventDispatcher();
    //    dispatcher->removeEventListener(_touchListener);
    //    GameServer::getSingleton().removeListeners(this);
    //    Layer::onExit();
}

