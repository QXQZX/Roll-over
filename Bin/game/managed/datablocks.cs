$managedDatablockSet = new SimSet() {
   canSaveDynamicFields = "1";
      setType = "Datablocks";

   new t2dImageMapDatablock(day_yard_bgImageMap1) {
      imageName = "~/data/images/day_yard_bg.jpg";
      imageMode = "FULL";
      frameCount = "-1";
      filterMode = "SMOOTH";
      filterPad = "0";
      preferPerf = "0";
      cellRowOrder = "1";
      cellOffsetX = "0";
      cellOffsetY = "0";
      cellStrideX = "0";
      cellStrideY = "0";
      cellCountX = "-1";
      cellCountY = "-1";
      cellWidth = "0";
      cellHeight = "0";
      preload = "0";
      allowUnload = "0";
      force16Bit = "0";
   };
   new t2dImageMapDatablock(PeaShooterImageMap1) {
      imageName = "~/data/images/PeaShooter.png";
      imageMode = "CELL";
      frameCount = "-1";
      filterMode = "SMOOTH";
      filterPad = "0";
      preferPerf = "0";
      cellRowOrder = "1";
      cellOffsetX = "0";
      cellOffsetY = "0";
      cellStrideX = "0";
      cellStrideY = "0";
      cellCountX = "13";
      cellCountY = "1";
      cellWidth = "63";
      cellHeight = "70";
      preload = "0";
      allowUnload = "0";
      force16Bit = "0";
   };
   new t2dImageMapDatablock(SunFlowerImageMap) {
      imageName = "~/data/images/SunFlower.png";
      imageMode = "CELL";
      frameCount = "-1";
      filterMode = "SMOOTH";
      filterPad = "0";
      preferPerf = "0";
      cellRowOrder = "1";
      cellOffsetX = "0";
      cellOffsetY = "0";
      cellStrideX = "0";
      cellStrideY = "0";
      cellCountX = "18";
      cellCountY = "1";
      cellWidth = "73";
      cellHeight = "74";
      preload = "0";
      allowUnload = "0";
      force16Bit = "0";
   };
   new t2dImageMapDatablock(ZombieImageMap1) {
      imageName = "~/data/images/Zombie.png";
      imageMode = "CELL";
      frameCount = "-1";
      filterMode = "SMOOTH";
      filterPad = "0";
      preferPerf = "0";
      cellRowOrder = "1";
      cellOffsetX = "0";
      cellOffsetY = "0";
      cellStrideX = "0";
      cellStrideY = "0";
      cellCountX = "22";
      cellCountY = "1";
      cellWidth = "87";
      cellHeight = "124";
      preload = "0";
      allowUnload = "0";
      force16Bit = "0";
   };
   new t2dImageMapDatablock(DandanTarget1ImageMap) {
      imageName = "~/data/images/DandanTarget1.dds";
      imageMode = "CELL";
      frameCount = "-1";
      filterMode = "SMOOTH";
      filterPad = "1";
      preferPerf = "1";
      cellRowOrder = "1";
      cellOffsetX = "0";
      cellOffsetY = "0";
      cellStrideX = "0";
      cellStrideY = "0";
      cellCountX = "4";
      cellCountY = "4";
      cellWidth = "64";
      cellHeight = "92";
      preload = "1";
      allowUnload = "0";
      force16Bit = "0";
   };
   new t2dAnimationDatablock(DandanTargetAnimation1) {
      imageMap = "DandanTarget1ImageMap";
      animationFrames = "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15";
      animationTime = "0.533333";
      animationCycle = "1";
      randomStart = "0";
      startFrame = "0";
      animationPingPong = "0";
      animationReverse = "0";
   };
   new t2dAnimationDatablock(PeaShooterAnimation) {
      imageMap = "PeaShooterImageMap1";
      animationFrames = "0 1 2 3 4 5 6 7 8 9 10 11 12";
      animationTime = "1";
      animationCycle = "1";
      randomStart = "0";
      startFrame = "0";
      animationPingPong = "0";
      animationReverse = "0";
   };
   new t2dAnimationDatablock(ZombieAnimation) {
      imageMap = "ZombieImageMap1";
      animationFrames = "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21";
      animationTime = "1";
      animationCycle = "1";
      randomStart = "0";
      startFrame = "0";
      animationPingPong = "0";
      animationReverse = "0";
   };
   new t2dImageMapDatablock(SnowPeaShooterImageMap1) {
      imageName = "~/data/images/SnowPeaShooter.png";
      imageMode = "CELL";
      frameCount = "-1";
      filterMode = "SMOOTH";
      filterPad = "0";
      preferPerf = "0";
      cellRowOrder = "1";
      cellOffsetX = "0";
      cellOffsetY = "0";
      cellStrideX = "0";
      cellStrideY = "0";
      cellCountX = "15";
      cellCountY = "1";
      cellWidth = "71";
      cellHeight = "71";
      preload = "0";
      allowUnload = "0";
      force16Bit = "0";
   };
   new t2dAnimationDatablock(SnowPeaShooterAnimation) {
      imageMap = "SnowPeaShooterImageMap1";
      animationFrames = "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14";
      animationTime = "1";
      animationCycle = "1";
      randomStart = "0";
      startFrame = "0";
      animationPingPong = "0";
      animationReverse = "0";
   };
};
