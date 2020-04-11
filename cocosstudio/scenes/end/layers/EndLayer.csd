<GameFile>
  <PropertyGroup Name="EndLayer" Type="Layer" ID="099f45ba-d8b7-4aa6-94ae-792dcdb03e47" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" Tag="18" ctype="GameLayerObjectData">
        <Size X="480.0000" Y="800.0000" />
        <Children>
          <AbstractNodeData Name="bg" ActionTag="-303689430" Tag="19" IconVisible="False" ctype="SpriteObjectData">
            <Size X="480.0000" Y="800.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="scenes/end/image/finish_bg.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="scoreSp" ActionTag="703842581" Tag="20" IconVisible="False" LeftMargin="32.5941" RightMargin="207.4059" TopMargin="169.6504" BottomMargin="580.3496" ctype="SpriteObjectData">
            <Size X="240.0000" Y="50.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="152.5941" Y="605.3496" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.3179" Y="0.7567" />
            <PreSize X="0.5000" Y="0.0625" />
            <FileData Type="Normal" Path="scenes/end/image/final_score.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="scoreNumberText" ActionTag="1241651818" Tag="21" IconVisible="False" LeftMargin="250.0000" RightMargin="216.0000" TopMargin="186.0000" BottomMargin="596.0000" CharWidth="14" CharHeight="18" LabelText="0" StartChar="." ctype="TextAtlasObjectData">
            <Size X="14.0000" Y="18.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="250.0000" Y="605.0000" />
            <Scale ScaleX="1.8000" ScaleY="1.8000" />
            <CColor A="255" R="27" G="250" B="31" />
            <PrePosition X="0.5208" Y="0.7563" />
            <PreSize X="0.0292" Y="0.0225" />
            <LabelAtlasFileImage_CNB Type="Default" Path="Default/TextAtlas.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="backMenuBtn" ActionTag="-575876297" Tag="29" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="130.0000" RightMargin="130.0000" TopMargin="562.5000" BottomMargin="162.5000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="190" Scale9Height="53" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="220.0000" Y="75.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="240.0000" Y="200.0000" />
            <Scale ScaleX="0.8500" ScaleY="0.8500" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.2500" />
            <PreSize X="0.4583" Y="0.0938" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="scenes/end/image/backMenu_pressed.png" Plist="" />
            <NormalFileData Type="Normal" Path="scenes/end/image/backMenu_normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="gameOverSp" ActionTag="624831335" Tag="30" IconVisible="False" PositionPercentXEnabled="True" LeftMargin="120.0000" RightMargin="120.0000" TopMargin="78.8740" BottomMargin="671.1260" ctype="SpriteObjectData">
            <Size X="240.0000" Y="50.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="240.0000" Y="696.1260" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.8702" />
            <PreSize X="0.5000" Y="0.0625" />
            <FileData Type="Normal" Path="scenes/end/image/game_over.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>