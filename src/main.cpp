#include <iostream>
#include "functions.h"

int main() {
    std::cout << "Features:\n";

    std::cout << "\n1. enciphering\n";
    std::string plainText = "насамомкраюселамироносицкоговсараестаростыпрокофиярасположилисьнаночлегзапоздавшиеохотникиихбылотолькодвоеветеринарныйврачиваниванычиучительгимназиибуркинуиванаиванычабыладовольностраннаядвойнаяфамилиячимшагималайскийкотораясовсемнешлаемуиегововсейгуберниизвалипростопоименииотчествуонжилокологороданаконскомзаводеиприехалтеперьнаохотучтобыподышатьчистымвоздухомучительжегимназиибуркинкаждоелетогостилуграфовпивэтойместностидавноужебылсвоимчеловекомнеспалииваниванычвысокийхудощавыйстариксдлиннымиусамисиделснаружиувходаикурилтрубкуегоосвещалалунабуркинлежалвнутринасенеиегонебыловидновпотемкахрассказывалиразныеисториимеждупрочимговорилиотомчтоженастаростымавраженщиназдороваяинеглупаявовсюсвоюжизньнигденебыладальшесвоегородногоселаникогданевиделанигороданижелезнойдорогиавпоследниедесятьлетвсесиделазапечьюитолькопоночамвыходиланаулицучтожетутудивительногосказалбуркинлюдейодинокихпонатурекоторыекакракотшелышкилиулиткастараютсяуйтивсвоюскорлупунаэтомсветенемалобытьможеттутявлениеатавизмавозвращениектомувременикогдапредокчеловеканебылещеобщественнымживотными";
    auto text = utf16ToInt(plainText);
    auto key1 = utf16ToInt("человеквфутляре");
    auto encryptedText = encrypt(text, key1);
    outputVector(intToUtf16(encryptedText));

    std::cout << "\n2. deciphering\n";
    auto decryptedText = decrypt(encryptedText, key1);
    outputVector(intToUtf16(decryptedText));

    std::cout << "\n3. cryptanalysis of text from resources/encipheredText.txt\n";
    auto cipher = readRawData("../resources/encipheredText.txt");
    auto encryptedData = utf16ToInt(cipher);

    auto keyLength = calcKeyLength(encryptedData);
    auto mainKey = decryptKey(encryptedData, keyLength);

    auto key = intToUtf16(mainKey);
    std::cout << "\nkey: ";
    outputVector(key);

    auto decryptedData = decrypt(encryptedData, mainKey);
    auto finalData = intToUtf16(decryptedData);
    outputData(finalData, "../resources/output.txt");
    std::cout << "\nafter cryptanalysis plain text was saved to resources/output.txt\n";

    return 0;
}
