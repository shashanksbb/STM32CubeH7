/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/recipeselectedscreen_screen/RecipeSelectedScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

RecipeSelectedScreenViewBase::RecipeSelectedScreenViewBase() :
    flexButtonCallback(this, &RecipeSelectedScreenViewBase::flexButtonCallbackHandler)
{
    scrollableContainerRecipe.setPosition(0, 0, 480, 272);
    scrollableContainerRecipe.enableHorizontalScroll(false);
    scrollableContainerRecipe.setScrollbarsColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    boxBg.setPosition(0, 320, 480, 985);
    boxBg.setColor(touchgfx::Color::getColorFrom24BitRGB(42, 33, 28));
    scrollableContainerRecipe.add(boxBg);

    imageDish.setXY(0, 0);
    imageDish.setBitmap(touchgfx::Bitmap(BITMAP_PASTE_BIG_BG_ID));
    scrollableContainerRecipe.add(imageDish);

    flexButtonBack.setIconBitmaps(Bitmap(BITMAP_GO_BACK_ID), Bitmap(BITMAP_GO_BACK_ID));
    flexButtonBack.setIconXY(22, 21);
    flexButtonBack.setPosition(0, 0, 82, 78);
    flexButtonBack.setAction(flexButtonCallback);
    scrollableContainerRecipe.add(flexButtonBack);

    imageDifficulty.setXY(210, 247);
    imageDifficulty.setBitmap(touchgfx::Bitmap(BITMAP_DIFFICULTY_ICON_ID));
    scrollableContainerRecipe.add(imageDifficulty);

    imageTimeIcon.setXY(118, 247);
    imageTimeIcon.setBitmap(touchgfx::Bitmap(BITMAP_TIME_ICON_ID));
    scrollableContainerRecipe.add(imageTimeIcon);

    imagePlatesIcon.setXY(303, 247);
    imagePlatesIcon.setBitmap(touchgfx::Bitmap(BITMAP_PLATES_ICON_ID));
    scrollableContainerRecipe.add(imagePlatesIcon);

    imageHeadline.setXY(22, 320);
    imageHeadline.setBitmap(touchgfx::Bitmap(BITMAP_TOP_TEXT_ID));
    scrollableContainerRecipe.add(imageHeadline);

    textAreaIngredientAmount1.setXY(28, 459);
    textAreaIngredientAmount1.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount1.setLinespacing(0);
    textAreaIngredientAmount1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID6));
    scrollableContainerRecipe.add(textAreaIngredientAmount1);

    textAreaIngredientAmount2.setXY(28, 483);
    textAreaIngredientAmount2.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount2.setLinespacing(0);
    textAreaIngredientAmount2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID7));
    scrollableContainerRecipe.add(textAreaIngredientAmount2);

    textAreaIngredientAmount3.setXY(28, 507);
    textAreaIngredientAmount3.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount3.setLinespacing(0);
    textAreaIngredientAmount3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID8));
    scrollableContainerRecipe.add(textAreaIngredientAmount3);

    textAreaIngredientAmoun4.setXY(28, 531);
    textAreaIngredientAmoun4.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmoun4.setLinespacing(0);
    textAreaIngredientAmoun4.setTypedText(touchgfx::TypedText(T_SINGLEUSEID9));
    scrollableContainerRecipe.add(textAreaIngredientAmoun4);

    textAreaIngredientAmount5.setXY(28, 555);
    textAreaIngredientAmount5.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount5.setLinespacing(0);
    textAreaIngredientAmount5.setTypedText(touchgfx::TypedText(T_SINGLEUSEID10));
    scrollableContainerRecipe.add(textAreaIngredientAmount5);

    textAreaIngredientAmount6.setXY(28, 579);
    textAreaIngredientAmount6.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount6.setLinespacing(0);
    textAreaIngredientAmount6.setTypedText(touchgfx::TypedText(T_SINGLEUSEID11));
    scrollableContainerRecipe.add(textAreaIngredientAmount6);

    textAreaIngredientAmount7.setXY(28, 603);
    textAreaIngredientAmount7.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount7.setLinespacing(0);
    textAreaIngredientAmount7.setTypedText(touchgfx::TypedText(T_SINGLEUSEID12));
    scrollableContainerRecipe.add(textAreaIngredientAmount7);

    textAreaIngredientAmount8.setXY(28, 627);
    textAreaIngredientAmount8.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount8.setLinespacing(0);
    textAreaIngredientAmount8.setTypedText(touchgfx::TypedText(T_SINGLEUSEID13));
    scrollableContainerRecipe.add(textAreaIngredientAmount8);

    textAreaIngredientAmount9.setXY(28, 651);
    textAreaIngredientAmount9.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredientAmount9.setLinespacing(0);
    textAreaIngredientAmount9.setTypedText(touchgfx::TypedText(T_SINGLEUSEID14));
    scrollableContainerRecipe.add(textAreaIngredientAmount9);

    textAreaIngredient1.setXY(173, 459);
    textAreaIngredient1.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient1.setLinespacing(0);
    textAreaIngredient1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID15));
    scrollableContainerRecipe.add(textAreaIngredient1);

    textAreaIngredient2.setXY(173, 483);
    textAreaIngredient2.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient2.setLinespacing(0);
    textAreaIngredient2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID16));
    scrollableContainerRecipe.add(textAreaIngredient2);

    textAreaIngredient3.setXY(173, 507);
    textAreaIngredient3.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient3.setLinespacing(0);
    textAreaIngredient3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID17));
    scrollableContainerRecipe.add(textAreaIngredient3);

    textAreaIngredient4.setXY(173, 531);
    textAreaIngredient4.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient4.setLinespacing(0);
    textAreaIngredient4.setTypedText(touchgfx::TypedText(T_SINGLEUSEID18));
    scrollableContainerRecipe.add(textAreaIngredient4);

    textAreaIngredient5.setXY(173, 555);
    textAreaIngredient5.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient5.setLinespacing(0);
    textAreaIngredient5.setTypedText(touchgfx::TypedText(T_SINGLEUSEID19));
    scrollableContainerRecipe.add(textAreaIngredient5);

    textAreaIngredient6.setXY(173, 579);
    textAreaIngredient6.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient6.setLinespacing(0);
    textAreaIngredient6.setTypedText(touchgfx::TypedText(T_SINGLEUSEID20));
    scrollableContainerRecipe.add(textAreaIngredient6);

    textAreaIngredient7.setXY(173, 603);
    textAreaIngredient7.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient7.setLinespacing(0);
    textAreaIngredient7.setTypedText(touchgfx::TypedText(T_SINGLEUSEID21));
    scrollableContainerRecipe.add(textAreaIngredient7);

    textAreaIngredient8.setXY(173, 627);
    textAreaIngredient8.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient8.setLinespacing(0);
    textAreaIngredient8.setTypedText(touchgfx::TypedText(T_SINGLEUSEID22));
    scrollableContainerRecipe.add(textAreaIngredient8);

    textAreaIngredient9.setXY(173, 651);
    textAreaIngredient9.setColor(touchgfx::Color::getColorFrom24BitRGB(215, 215, 215));
    textAreaIngredient9.setLinespacing(0);
    textAreaIngredient9.setTypedText(touchgfx::TypedText(T_SINGLEUSEID23));
    scrollableContainerRecipe.add(textAreaIngredient9);

    textAreaIngredientHeadline.setXY(28, 423);
    textAreaIngredientHeadline.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 134, 7));
    textAreaIngredientHeadline.setLinespacing(0);
    textAreaIngredientHeadline.setTypedText(touchgfx::TypedText(T_SINGLEUSEID24));
    scrollableContainerRecipe.add(textAreaIngredientHeadline);

    boxLine2.setPosition(30, 708, 420, 1);
    boxLine2.setColor(touchgfx::Color::getColorFrom24BitRGB(72, 53, 43));
    scrollableContainerRecipe.add(boxLine2);

    textAreaMethodHeadline.setXY(28, 742);
    textAreaMethodHeadline.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 134, 7));
    textAreaMethodHeadline.setLinespacing(0);
    textAreaMethodHeadline.setTypedText(touchgfx::TypedText(T_SINGLEUSEID27));
    scrollableContainerRecipe.add(textAreaMethodHeadline);

    textAreaStep1Headline.setXY(28, 781);
    textAreaStep1Headline.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textAreaStep1Headline.setLinespacing(0);
    textAreaStep1Headline.setTypedText(touchgfx::TypedText(T_SINGLEUSEID28));
    scrollableContainerRecipe.add(textAreaStep1Headline);

    textAreaStep1Directions.setXY(28, 813);
    textAreaStep1Directions.setColor(touchgfx::Color::getColorFrom24BitRGB(203, 202, 202));
    textAreaStep1Directions.setLinespacing(0);
    textAreaStep1Directions.setTypedText(touchgfx::TypedText(T_SINGLEUSEID29));
    scrollableContainerRecipe.add(textAreaStep1Directions);

    textAreaStep2Headline.setXY(28, 904);
    textAreaStep2Headline.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textAreaStep2Headline.setLinespacing(0);
    textAreaStep2Headline.setTypedText(touchgfx::TypedText(T_SINGLEUSEID30));
    scrollableContainerRecipe.add(textAreaStep2Headline);

    textAreaStep2Directions.setXY(28, 936);
    textAreaStep2Directions.setColor(touchgfx::Color::getColorFrom24BitRGB(203, 202, 202));
    textAreaStep2Directions.setLinespacing(0);
    textAreaStep2Directions.setTypedText(touchgfx::TypedText(T_SINGLEUSEID31));
    scrollableContainerRecipe.add(textAreaStep2Directions);

    textAreaStep3Headline.setXY(28, 1075);
    textAreaStep3Headline.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textAreaStep3Headline.setLinespacing(0);
    textAreaStep3Headline.setTypedText(touchgfx::TypedText(T_SINGLEUSEID32));
    scrollableContainerRecipe.add(textAreaStep3Headline);

    textAreaStep3Directions.setXY(28, 1107);
    textAreaStep3Directions.setColor(touchgfx::Color::getColorFrom24BitRGB(203, 202, 202));
    textAreaStep3Directions.setLinespacing(0);
    textAreaStep3Directions.setTypedText(touchgfx::TypedText(T_SINGLEUSEID33));
    scrollableContainerRecipe.add(textAreaStep3Directions);

    boxLine3.setPosition(30, 1207, 156, 1);
    boxLine3.setColor(touchgfx::Color::getColorFrom24BitRGB(72, 53, 43));
    scrollableContainerRecipe.add(boxLine3);

    boxLine4.setPosition(292, 1207, 158, 1);
    boxLine4.setColor(touchgfx::Color::getColorFrom24BitRGB(72, 53, 43));
    scrollableContainerRecipe.add(boxLine4);

    textAreaNutritionHeadline.setXY(200, 1193);
    textAreaNutritionHeadline.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textAreaNutritionHeadline.setLinespacing(0);
    textAreaNutritionHeadline.setTypedText(touchgfx::TypedText(T_SINGLEUSEID34));
    scrollableContainerRecipe.add(textAreaNutritionHeadline);

    textAreaNutritionValue1.setXY(48, 1217);
    textAreaNutritionValue1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 134, 7));
    textAreaNutritionValue1.setLinespacing(0);
    textAreaNutritionValue1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID35));
    scrollableContainerRecipe.add(textAreaNutritionValue1);

    textAreaNutritionValue2.setXY(143, 1217);
    textAreaNutritionValue2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 134, 7));
    textAreaNutritionValue2.setLinespacing(0);
    textAreaNutritionValue2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID36));
    scrollableContainerRecipe.add(textAreaNutritionValue2);

    textAreaNutritionValue3.setXY(219, 1217);
    textAreaNutritionValue3.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 134, 7));
    textAreaNutritionValue3.setLinespacing(0);
    textAreaNutritionValue3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID37));
    scrollableContainerRecipe.add(textAreaNutritionValue3);

    textAreaNutritionValue4.setXY(305, 1217);
    textAreaNutritionValue4.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 134, 7));
    textAreaNutritionValue4.setLinespacing(0);
    textAreaNutritionValue4.setTypedText(touchgfx::TypedText(T_SINGLEUSEID38));
    scrollableContainerRecipe.add(textAreaNutritionValue4);

    textAreaNutritionValue5.setXY(392, 1217);
    textAreaNutritionValue5.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 134, 7));
    textAreaNutritionValue5.setLinespacing(0);
    textAreaNutritionValue5.setTypedText(touchgfx::TypedText(T_SINGLEUSEID39));
    scrollableContainerRecipe.add(textAreaNutritionValue5);

    textAreatextAreaNutritionType1.setXY(60, 1243);
    textAreatextAreaNutritionType1.setColor(touchgfx::Color::getColorFrom24BitRGB(146, 144, 143));
    textAreatextAreaNutritionType1.setLinespacing(0);
    textAreatextAreaNutritionType1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID40));
    scrollableContainerRecipe.add(textAreatextAreaNutritionType1);

    textAreatextAreaNutritionType2.setXY(144, 1243);
    textAreatextAreaNutritionType2.setColor(touchgfx::Color::getColorFrom24BitRGB(146, 144, 143));
    textAreatextAreaNutritionType2.setLinespacing(0);
    textAreatextAreaNutritionType2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID41));
    scrollableContainerRecipe.add(textAreatextAreaNutritionType2);

    textAreatextAreaNutritionType3.setXY(215, 1243);
    textAreatextAreaNutritionType3.setColor(touchgfx::Color::getColorFrom24BitRGB(146, 144, 143));
    textAreatextAreaNutritionType3.setLinespacing(0);
    textAreatextAreaNutritionType3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID42));
    scrollableContainerRecipe.add(textAreatextAreaNutritionType3);

    textAreatextAreaNutritionType4.setXY(304, 1243);
    textAreatextAreaNutritionType4.setColor(touchgfx::Color::getColorFrom24BitRGB(146, 144, 143));
    textAreatextAreaNutritionType4.setLinespacing(0);
    textAreatextAreaNutritionType4.setTypedText(touchgfx::TypedText(T_SINGLEUSEID43));
    scrollableContainerRecipe.add(textAreatextAreaNutritionType4);

    textAreatextAreaNutritionType5.setXY(386, 1243);
    textAreatextAreaNutritionType5.setColor(touchgfx::Color::getColorFrom24BitRGB(146, 144, 143));
    textAreatextAreaNutritionType5.setLinespacing(0);
    textAreatextAreaNutritionType5.setTypedText(touchgfx::TypedText(T_SINGLEUSEID44));
    scrollableContainerRecipe.add(textAreatextAreaNutritionType5);

    boxLine5.setPosition(30, 1269, 420, 1);
    boxLine5.setColor(touchgfx::Color::getColorFrom24BitRGB(72, 53, 43));
    scrollableContainerRecipe.add(boxLine5);

    boxLine6.setPosition(30, 1272, 420, 1);
    boxLine6.setColor(touchgfx::Color::getColorFrom24BitRGB(72, 53, 43));
    scrollableContainerRecipe.add(boxLine6);
    scrollableContainerRecipe.setScrollbarsVisible(false);

    add(scrollableContainerRecipe);
}

void RecipeSelectedScreenViewBase::setupScreen()
{

}

void RecipeSelectedScreenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &flexButtonBack)
    {
        //InteractionGoToRecipeSelect
        //When flexButtonBack clicked change screen to RecipeScreen
        //Go to RecipeScreen with screen transition towards South
        application().gotoRecipeScreenScreenCoverTransitionSouth();
    }
}
