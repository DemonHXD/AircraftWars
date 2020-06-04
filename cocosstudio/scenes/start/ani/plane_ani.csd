<GameFile>
  <PropertyGroup Name="plane_ani" Type="Node" ID="4b49b2bd-9bf4-4762-8edf-09ccddb6a7c0" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="160" Speed="1.0000" ActivedAnimationName="run">
        <Timeline ActionTag="1844848133" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="5.0000" Y="-5.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="80" X="5.0000" Y="-10.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="120" X="5.0000" Y="-5.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="160" X="2.0000" Y="-2.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1844848133" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.5000" Y="0.5000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1844848133" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="run" StartIndex="0" EndIndex="160">
          <RenderColor A="150" R="248" G="248" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="49" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="plane_ani_1_1" ActionTag="1844848133" Tag="50" IconVisible="False" LeftMargin="-141.5000" RightMargin="-151.5000" TopMargin="-73.5000" BottomMargin="-85.5000" ctype="SpriteObjectData">
            <Size X="293.0000" Y="159.0000" />
            <Children>
              <AbstractNodeData Name="plane_ani_2_2" ActionTag="888847865" Tag="51" RotationSkewX="-70.0000" RotationSkewY="-70.0000" IconVisible="False" PositionPercentYEnabled="True" LeftMargin="214.5000" RightMargin="-52.5000" TopMargin="-153.4000" BottomMargin="37.4000" ctype="SpriteObjectData">
                <Size X="131.0000" Y="275.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="280.0000" Y="174.9000" />
                <Scale ScaleX="0.9000" ScaleY="0.9000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.9556" Y="1.1000" />
                <PreSize X="0.4471" Y="1.7296" />
                <FileData Type="Normal" Path="scenes/start/image/plane_ani_2.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="5.0000" Y="-6.0000" />
            <Scale ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="scenes/start/image/plane_ani_1.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>