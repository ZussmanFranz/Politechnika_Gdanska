using UnityEngine;
using UnityEditor;

public class ChangePixelsPerUnit : EditorWindow
{
    private float newPixelsPerUnit = 100f; // Domyślna wartość, którą chcesz ustawić

    [MenuItem("Tools/Change Pixels Per Unit")]
    public static void ShowWindow()
    {
        GetWindow<ChangePixelsPerUnit>("Change Pixels Per Unit");
    }

    void OnGUI()
    {
        GUILayout.Label("Change Pixels Per Unit for all Textures", EditorStyles.boldLabel);

        newPixelsPerUnit = EditorGUILayout.FloatField("Pixels Per Unit", newPixelsPerUnit);

        if (GUILayout.Button("Change Pixels Per Unit"))
        {
            ChangeAllTexturesPixelsPerUnit(newPixelsPerUnit);
        }
    }

    void ChangeAllTexturesPixelsPerUnit(float ppu)
    {
        string[] textureGuids = AssetDatabase.FindAssets("t:Texture2D");
        foreach (string guid in textureGuids)
        {
            string path = AssetDatabase.GUIDToAssetPath(guid);
            TextureImporter textureImporter = AssetImporter.GetAtPath(path) as TextureImporter;

            if (textureImporter != null)
            {
                textureImporter.spritePixelsPerUnit = ppu;
                textureImporter.SaveAndReimport();
            }
        }

        Debug.Log("Pixels Per Unit changed for all textures to: " + ppu);
    }
}
