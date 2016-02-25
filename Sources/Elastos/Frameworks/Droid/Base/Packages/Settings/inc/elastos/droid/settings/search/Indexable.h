

package com.android.settings.search;

using Elastos::Droid::Content::IContext;
using Elastos::Droid::Provider::ISearchIndexableResource;

using Elastos::Utility::IList;

/**
 * Interface for classes whose instances can provide data for indexing.
 *
 * Classes implementing the Indexable interface must have a static field called
 * <code>SEARCH_INDEX_DATA_PROVIDER</code>, which is an object implementing the
 * {@link Indexable.SearchIndexProvider} interface.
 *
 * See {@link android.provider.SearchIndexableResource} and {@link SearchIndexableRaw}.
 *
 */
public interface Indexable {

    public interface SearchIndexProvider {
        /**
         * Return a list of references for indexing.
         *
         * See {@link android.provider.SearchIndexableResource}
         *
         *
         * @param context the context.
         * @param enabled hint telling if the data needs to be considered into the search results
         *                or not.
         * @return a list of {@link android.provider.SearchIndexableResource} references.
         *         Can be NULL.
         */
        List<SearchIndexableResource> GetXmlResourcesToIndex(Context context, Boolean enabled);

        /**
         * Return a list of raw data for indexing. See {@link SearchIndexableRaw}
         *
         * @param context the context.
         * @param enabled hint telling if the data needs to be considered into the search results
         *                or not.
         * @return a list of {@link SearchIndexableRaw} references. Can be NULL.
         */
        List<SearchIndexableRaw> GetRawDataToIndex(Context context, Boolean enabled);

        /**
         * Return a list of data keys that cannot be indexed. See {@link SearchIndexableRaw}
         *
         * @param context the context.
         * @return a list of {@link SearchIndexableRaw} references. Can be NULL.
         */
        List<String> GetNonIndexableKeys(Context context);
    }
}
