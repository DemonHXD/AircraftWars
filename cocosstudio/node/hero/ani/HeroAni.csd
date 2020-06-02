<GameFile>
  <PropertyGroup Name="HeroAni" Type="Node" ID="10d786d7-e2c3-472a-aed4-6808a21d5ac3" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="30" Speed="1.0000">
        <Timeline ActionTag="-1990691913" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="Normal" Path="node/hero/image/hero1_1.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="Normal" Path="node/hero/image/hero1_2.png" Plist="" />
          </TextureFrame>
          <TextureFrame FrameIndex="30" Tween="False">
            <TextureFile Type="Normal" Path="node/hero/image/hero1_1.png" Plist="" />
          </TextureFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="fly" StartIndex="0" EndIndex="30">
          <RenderColor A="150" R="250" G="240" B="230" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="16" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Sprite_1" ActionTag="-1990691913" Tag="17" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
            <Size X="93.0000" Y="129.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="node/hero/image/hero1_1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>